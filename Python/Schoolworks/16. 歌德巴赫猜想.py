import math

def is_prime(n):
    if n <= 1:
        return False
    for i in range(2,int(math.sqrt(n))+1):
        if n % i == 0:
            return False
    return True

n = int(input())
for even in range(4,n+1,2):
    for i in range(2, even // 2 + 1):
        j = even - i
        if is_prime(i) and is_prime(j):
            print(f"{even}={i}+{j}")
            break  # 找到一个分解就跳出，继续下一个偶数
        
            
