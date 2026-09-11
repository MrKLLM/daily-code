def count_digits(n):
    """
    统计整数 n 的各位上出现数字 0~9 的次数
    :param n: 整数（可以为负，取绝对值处理）
    :return: 包含10个整数的列表，分别表示0~9的出现次数
    """
    # 初始化计数数组，索引0对应数字0的次数，索引1对应数字1的次数...
    counts = [0] * 10
    
    # 处理负数情况
    n = abs(n)
    
    # 特殊情况：如果 n 为 0，则数字 0 出现 1 次
    if n == 0:
        counts[0] = 1
        return counts
    
    # 逐位提取并统计
    while n > 0:
        digit = n % 10      # 取最后一位
        counts[digit] += 1  # 对应数字计数+1
        n //= 10            # 去掉最后一位
    
    return counts


# 主程序：输入与输出（不在自定义函数内）
if __name__ == "__main__":
    num = int(input())
    result = count_digits(num)
    # 将结果列表转换为用空格分隔的字符串输出
    print(" ".join(map(str, result)))
