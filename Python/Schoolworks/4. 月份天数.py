def show_days(year,month):
    if month in [1,3,5,7,8,10,12]:
        print(31)
    elif month in [4,6,9,11]:
        print(30)
    else:
        if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
            print(29)  # 闰年2月有29天
        else:
            print(28)  # 平年2月有28天

y,m = map(int,input().split())
show_days(y,m)
