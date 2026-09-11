import math

a ,b ,c = map(float,input().split())

delta = b**2 - 4*a*c

if delta<0:
    print("No")
else:
    sqrt_delta = math.sqrt(delta)

    x1 = (-b + sqrt_delta) / (2*a)
    x2 = (-b - sqrt_delta) / (2*a)

    if x1<x2:
        x1,x2 = x2,x1
    print(f"{x1:.2f} {x2:.2f}")
