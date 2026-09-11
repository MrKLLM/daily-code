import math

def is_prime(n):
    if n <= 1:
        return False
    for i in range(2,int(math.sqrt(n))+1):
        if n % i == 0:
            return False
    return True

try:
    num = int(input())

    reversed_num_str = str(num)[::-1]
    reversed_num = int(reversed_num_str)

    if is_prime(reversed_num) and is_prime(num):
        print("yes")
    else:
        print("no")

except ValueError:
    # 处理非数字输入的情况，加上更鲁棒
    print("no")
