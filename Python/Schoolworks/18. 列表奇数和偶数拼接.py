nums = list(map(int, input().split()))

odds = []
evens = []

for num in nums:
    if num % 2 != 0:
        odds.append(num)
    else:
        evens.append(num)
odds.sort(reverse=True)
evens.sort()
result = odds + evens
print(result)
