nums = list(map(int,input().split()))

evens = [x for x in nums if x % 2 == 0]

evens.sort()

print(" ".join(map(str,evens)))
