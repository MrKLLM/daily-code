def fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib(n - 1) + fib(n - 2)

# 读取输入
n = int(input())

# 输出结果
print(fib(n))
