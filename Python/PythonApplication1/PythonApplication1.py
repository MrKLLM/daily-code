# -*- coding: utf-8 -*-
from PIL import Image
import os
import sys

def parse_obj(obj_path):
    # ... (这部分代码保持不变) ...
    vertices = []
    uvs = []
    faces = []

    with open(obj_path, 'r', encoding='utf-8') as f:
        for line_num, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue

            parts = line.split()
            if parts[0] == 'v':
                try:
                    x = float(parts[1])
                    y = float(parts[2])
                    z = float(parts[3]) if len(parts) >= 4 else 0.0
                    vertices.append((x, y, z))
                except (IndexError, ValueError):
                    print(f"[警告] 跳过无效顶点行（第{line_num}行）：{line}")
                    continue

            elif parts[0] == 'vt':
                try:
                    u = float(parts[1])
                    v = float(parts[2])
                    uvs.append((u, v))
                except (IndexError, ValueError):
                    print(f"[警告] 跳过无效UV行（第{line_num}行）：{line}")
                    continue

            elif parts[0] == 'f':
                face_vertex_count = len(parts) - 1
                if face_vertex_count not in (3, 4):
                    print(f"[警告] 跳过非三角/四边形面（第{line_num}行）：{line}")
                    continue

                face_v_idx = []
                face_vt_idx = []
                for part in parts[1:1+face_vertex_count]:
                    try:
                        parts_split = part.split('/')
                        v_part = parts_split[0] if len(parts_split) > 0 else ''
                        vt_part = parts_split[1] if len(parts_split) > 1 else ''
                        
                        v_idx = int(v_part) - 1
                        vt_idx = int(vt_part) - 1 if vt_part else -1
                    except (ValueError, IndexError):
                        print(f"[警告] 跳过无效面顶点（第{line_num}行）：{part}")
                        continue

                    if 0 <= v_idx < len(vertices) and 0 <= vt_idx < len(uvs):
                        face_v_idx.append(v_idx)
                        face_vt_idx.append(vt_idx)
                
                if len(face_v_idx) == face_vertex_count and len(face_vt_idx) == face_vertex_count:
                    faces.append({
                        'v_idx': face_v_idx,
                        'vt_idx': face_vt_idx
                    })

    print(f"[解析结果] 顶点数：{len(vertices)}，UV数：{len(uvs)}，有效面数：{len(faces)}")
    return vertices, uvs, faces

def get_tile_from_uv(source_img, uv_coords):
    # ... (这部分代码保持不变) ...
    img_width, img_height = source_img.size
    pixel_coords = []
    for u, v in uv_coords:
        u_clamped = max(0.0, min(1.0, u))
        v_clamped = max(0.0, min(1.0, v))
        
        x = int(round(u_clamped * (img_width - 1)))
        y = int(round((1 - v_clamped) * (img_height - 1)))
        pixel_coords.append((x, y))
    
    min_x = min(p[0] for p in pixel_coords)
    max_x = max(p[0] for p in pixel_coords)
    min_y = min(p[1] for p in pixel_coords)
    max_y = max(p[1] for p in pixel_coords)
    
    return source_img.crop((min_x, min_y, max_x + 1, max_y + 1))

def stitch_image(source_png_path, obj_path, output_path):
    try:
        source_img = Image.open(source_png_path).convert('RGBA')
        src_w, src_h = source_img.size
        print(f"\n成功读取源图片：{source_png_path}（尺寸：{src_w}x{src_h}）")
    except Exception as e:
        print(f"读取源图片失败：{e}")
        return False

    vertices, uvs, faces = parse_obj(obj_path)
    if not vertices or not uvs or not faces:
        print("OBJ文件解析失败，无有效顶点/UV/面信息")
        return False

    # --- 步骤 1: 找出所有顶点在世界空间中的边界 ---
    all_world_x = [v[0] for v in vertices]
    all_world_y = [v[1] for v in vertices]
    
    min_world_x, max_world_x = min(all_world_x), max(all_world_x)
    min_world_y, max_world_y = min(all_world_y), max(all_world_y)
    
    world_width = max_world_x - min_world_x
    world_height = max_world_y - min_world_y

    if world_width == 0: world_width = 1.0
    if world_height == 0: world_height = 1.0

    print(f"[世界坐标范围] X: [{min_world_x:.2f}, {max_world_x:.2f}], Y: [{min_world_y:.2f}, {max_world_y:.2f}]")

    # --- 步骤 2: 计算目标画布的尺寸和偏移量 ---
    target_width = int(round(max_world_x - min_world_x))
    target_height = int(round(max_world_y - min_world_y))
    
    target_img = Image.new('RGBA', (target_width, target_height), (0, 0, 0, 0))
    print(f"[创建画布] 尺寸: {target_width}x{target_height} (最小包围盒)")

    # --- 步骤 3: 坐标转换与深度排序 ---
    for face in faces:
        z_values = [vertices[v_idx][2] for v_idx in face['v_idx']]
        face['avg_z'] = sum(z_values) / len(z_values)
    faces.sort(key=lambda f: f['avg_z'])

    # --- 步骤 4: 粘贴所有图片块（修改坐标反转逻辑）---
    for idx, face in enumerate(faces, 1):
        uv_coords = [uvs[vt_idx] for vt_idx in face['vt_idx']]
        tile = get_tile_from_uv(source_img, uv_coords)
        
        # 获取面的世界坐标
        face_world_coords = [vertices[v_idx][:2] for v_idx in face['v_idx']]
        
        # 关键修改：同时反转X轴和Y轴的方向
        face_canvas_coords = [
            (
                target_width - (x - min_world_x),  # X轴反转（左右颠倒修正）
                target_height - (y - min_world_y)  # Y轴反转（上下颠倒修正）
            ) 
            for x, y in face_world_coords
        ]
        
        # 计算放置位置
        dest_min_x = int(round(min(p[0] for p in face_canvas_coords)))
        dest_min_y = int(round(min(p[1] for p in face_canvas_coords)))
        
        dest_max_x = int(round(max(p[0] for p in face_canvas_coords)))
        dest_max_y = int(round(max(p[1] for p in face_canvas_coords)))
        tile_width = dest_max_x - dest_min_x
        tile_height = dest_max_y - dest_min_y
        
        if tile_width <= 0 or tile_height <= 0:
            print(f"[警告] 跳过过小的图片块（第{idx}块）")
            continue

        tile_resized = tile.resize((tile_width, tile_height), Image.Resampling.LANCZOS)
        target_img.paste(tile_resized, (dest_min_x, dest_min_y), tile_resized)
        
        if idx % 10 == 0:
            print(f"已拼接第 {idx}/{len(faces)} 块...")

    try:
        target_img.save(output_path)
        print(f"\n拼接完成！结果已保存到：{output_path}")
        return True
    except Exception as e:
        print(f"保存图片失败：{e}")
        return False

def batch_stitch(png_folder, obj_folder, output_folder):
    if not os.path.exists(png_folder):
        print(f"PNG文件夹不存在：{png_folder}")
        sys.exit(1)
    if not os.path.exists(obj_folder):
        print(f"OBJ文件夹不存在：{obj_folder}")
        sys.exit(1)
    
    os.makedirs(output_folder, exist_ok=True)
    print(f"输出文件夹：{output_folder}\n")

    for filename in os.listdir(png_folder):
        if not filename.lower().endswith('.png'):
            continue
        
        png_path = os.path.join(png_folder, filename)
        obj_filename = os.path.splitext(filename)[0] + '.obj'
        obj_path = os.path.join(obj_folder, obj_filename)
        
        if not os.path.exists(obj_path):
            print(f"跳过 {filename}：未找到对应的OBJ文件 {obj_filename}\n")
            continue
        
        output_path = os.path.join(output_folder, filename)
        print(f"===== 开始处理：{filename} =====")
        stitch_image(png_path, obj_path, output_path)

    print("\n所有图片处理完成！")

if __name__ == "__main__":
    PNG_FOLDER = "E:\\painting(unordered)\\Texture2D"
    OBJ_FOLDER = "E:\\painting(unordered)\\Mesh"
    OUTPUT_FOLDER = "E:\\PPPaintings"

    batch_stitch(PNG_FOLDER, OBJ_FOLDER, OUTPUT_FOLDER)