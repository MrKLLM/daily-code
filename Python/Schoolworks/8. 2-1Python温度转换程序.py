print()

temperature = input()
tmpera_digit = float(temperature[:-1])

if temperature[-1].upper() == "F":
    result = int(( tmpera_digit - 32.0 ) / 1.8)
    print(f"What is the temperature?The converted temperature is {result}C")
elif temperature[-1].upper() == "C":
    result = int(tmpera_digit * 1.8 + 32.0)
    print(f"What is the temperature?The converted temperature is {result}F")
