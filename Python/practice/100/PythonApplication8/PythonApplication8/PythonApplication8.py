def is_prime(num):
    if num <= 1:
        return False
    elif num == 2:
        return True
    elif num % 2 == 0:
        return False
    else:
        for i in range(3, int(num**0.5 + 1), 2):
            if num % i == 0:
                return False
        return True
            
def print_prime(start ,end):
    for i in range(start,end+1):
        if is_prime(i):
            print(i)

print_prime(start=int(input("start:")),end=int(input("end:")))