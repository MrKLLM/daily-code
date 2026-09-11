n = float(input())
m = int(input())
path_len = 0.0
current_h = n

for i in range(m):
    if i == 0:
        # 第一次落地：只有下落，没有反弹
        path_len += current_h
    else:
        # 后续落地：球先反弹到 current_h 高度，再落回地面
        # 所以增加的距离是 2 * current_h
        path_len += 2 * current_h
        
    # 计算下一次反弹的高度（如果是最后一次落地，这个高度就是题目要的第 m 次反弹高度）
    current_h *= 0.25
print(f"{path_len + 0.001:.2f}\n{current_h + 0.001:.2f}")
#加上 0.001 强制标准四舍五入，防止 0.625 变成 0.62
