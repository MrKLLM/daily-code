list1 = [1,2,3,4,5]
num = int(input())
for i in range(len(list1)):
    if list1[i] > num:
        list1.insert(i,num)
        break
else:
   list1.append(num)
print(list1)