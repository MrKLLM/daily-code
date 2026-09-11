nums = list(map(int, input().split()))

n = len(nums)
nums.sort()

if n%2 != 0:
    print(f"{nums[n//2]:.1f}")
else:
    mid = n // 2
    median = (nums[mid-1]+nums[mid]) / 2
    print(f"{median:.1f}")
