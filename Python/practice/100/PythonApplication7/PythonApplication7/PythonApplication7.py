import math


def area_of_circle(r):
    area =round( math.pi * r**2,2)
    return area
area = area_of_circle(int(input("请输入半径：")))
print(area)

print(round(math.pi,2))