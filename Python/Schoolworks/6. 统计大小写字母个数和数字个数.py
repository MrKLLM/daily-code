str1 = input()
upper_cnt = 0
lower_cnt = 0
digit_cnt = 0
for c in str1:
    if c.isupper():
        upper_cnt+=1
    elif c.islower():
        lower_cnt+=1
    elif c.isdigit():
        digit_cnt += 1

print(f"{upper_cnt}\n{lower_cnt}\n{digit_cnt}")
