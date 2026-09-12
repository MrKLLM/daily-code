using System.Collections.Generic;
using System.Linq.Expressions;

class Program
{
    static void Main(string[] args)
    {
        class Student
        {
            public int Id { get; set; }
            public string Name { get; set; }
        }
        class NewStudent
        {
            public int Id { get; set; }
            public string Name { get; set; }
        }
        Student stu = new Student { Id = 1, Name = "KLLM" };
        NewStudent newStu = new NewStudent();
        NewStudent newStu2 = ExpressionMapper<Student, NewStudent>().Mapper(stu);
           }
}
