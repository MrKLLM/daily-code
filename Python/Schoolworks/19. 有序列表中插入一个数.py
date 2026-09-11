nums = list(map(int, input().split()))
num = int(input())

nums.append(num)
nums.sort()

print(" ".join(map(str, nums)))
