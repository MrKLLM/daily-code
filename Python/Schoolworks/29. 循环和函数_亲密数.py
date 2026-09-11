def get_factor_sum(num):
    if num<2:
        return 0
    total = sum(i for i in range(1,num//2+1) if num % i == 0)
    return total

n = int(input())
result_pairs = []
for a in range(2,n+1):
    b = get_factor_sum(a)

    if a < b <=n :
        if get_factor_sum(b) == a:
            result_pairs.append((a,b))

result_pairs.sort()

for pair in result_pairs:
    print(f"{pair[0]} {pair[1]}")
