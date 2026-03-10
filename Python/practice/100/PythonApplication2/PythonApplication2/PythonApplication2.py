people = {"张三":13,"李四":27,"王五":82}
max_age = float('-inf')
max_name = ""
for name,age in people.items():
    if age > max_age:
        max_name = name
        max_age = age
print(f"{max_name}:{max_age}")
