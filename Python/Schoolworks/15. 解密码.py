def transform(s):
    """
    核心转换函数：将字符串中的字母按规律转换
    """
    result = []
    for char in s:
        if 'A' <= char <= 'Z':
            # 大写字母转换：找到相对于'A'的距离，再从'Z'往回数同样的距离
            new_char = chr(ord('Z') - (ord(char) - ord('A')))
            result.append(new_char)
        elif 'a' <= char <= 'z':
            # 小写字母转换：同理
            new_char = chr(ord('z') - (ord(char) - ord('a')))
            result.append(new_char)
        else:
            # 非字母字符直接保留
            result.append(char)
    return "".join(result)

# 1. 读取输入
password_input = input()

# 2. 生成密码（第一次转换）
encrypted_password = transform(password_input)

# 3. 解密得到原文（第二次转换）
original_text = transform(encrypted_password)

# 4. 按要求输出

print(original_text)
print(encrypted_password)
