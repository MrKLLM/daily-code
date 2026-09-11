year ,month ,day = map(int,input().split())

month_days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
    month_days[1] = 29

total_days = 0

for i in range(month-1):
    total_days += month_days[i]
total_days += day
print(total_days)
