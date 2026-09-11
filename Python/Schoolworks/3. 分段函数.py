def func(x):
    if x<5:
        return x;
    elif 5<=x<15:
        return x+6
    else:
        return x-6


num = int(input())

if num < 0:
    print("illegal input")
else:
    result = func(num)
    print(result)
