nums = list(map(int,input().split()))
result = []

for i in range(0,len(nums),2):
    rev_grp = nums[i:i+2][::-1]
    result.extend(rev_grp)

print(result)
