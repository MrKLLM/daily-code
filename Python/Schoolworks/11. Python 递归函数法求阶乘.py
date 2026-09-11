def jie_cheng(n):
    if n == 0 or n == 1:
        return 1
    else:
        return n*jie_cheng(n-1)
n = int(input())
print(jie_cheng(n))
