target = 100

while True:
    # 接收用户输入并转换为整数
    num = int(input())
    
    if num < target:
        print("less than expected")
    elif num > target:
        print("larger than expected")
    else:
        # 猜中时输出并结束程序
        print("you win")
        break
