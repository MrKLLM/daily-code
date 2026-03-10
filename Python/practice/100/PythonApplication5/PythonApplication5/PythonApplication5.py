num = int(input("输入一个数："))
n=1
while True:
    n_9 = int(9*n)
    if n_9 % num == 0:
        print(n_9)
        break
    n+=1
else:print("unexist")
