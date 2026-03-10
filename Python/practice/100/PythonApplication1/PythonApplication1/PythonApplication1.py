students = [
    {'sno':123,'sname':"子昂"},
    {'sno':13,'sname':"夹可奶"},
    {'sno':3,'sname':"安安"}
]
#匿名函数：只用一次，用lamda简化
studentsSort = sorted(students,key=lambda x:x["sname"])
print(studentsSort)