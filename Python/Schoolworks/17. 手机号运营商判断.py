phone_num1 = input().strip()

if len(phone_num1) != 11 or not phone_num1.isdigit():
    print ("格式错误")
elif phone_num1[:3] not in ("138","139","186","189"):
    print ("未知")
else:
    if phone_num1[:3] in ("138","139"):
        print ("移动")
    elif phone_num1[:3] in ("186","189"):
        print ("联通")
