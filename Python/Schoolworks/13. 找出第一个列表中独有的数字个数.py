list1 = list(map(int, input().split()))
list2 = list(map(int, input().split()))

count = 0
checked = []

for num in list1:
    if num in checked:
        continue
    
    if num not in list2:
        count += 1
    
    checked.append(num)

print(count)
"""
#读取第一行
line1 = input().split()
# 读取第二行
line2 = input().split()

# 转为整数集合（自动去重）
set1 = set(map(int, line1))
set2 = set(map(int, line2))

# 计算第一个列表独有的元素个数
unique_count = len(set1 - set2)

# 输出结果
print(unique_count)
"""
