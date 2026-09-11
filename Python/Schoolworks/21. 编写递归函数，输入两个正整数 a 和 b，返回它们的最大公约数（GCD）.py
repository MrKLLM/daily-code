def gcd(a, b):
    """递归函数求最大公约数"""
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

a, b = map(int, input().split())
print(gcd(a, b))
