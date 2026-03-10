for i in range(7):
    
    while True:
        num = int(input ("请输入一个0到50以内的数："))
        if 1<=num<=50:
            print("*" * num)
            break
        else:
            print("输入无效，请重新输入！")
