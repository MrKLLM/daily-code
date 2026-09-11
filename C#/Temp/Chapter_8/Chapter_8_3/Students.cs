using System;
using Models;

namespace Chapter_8_3
{
    class Program
    {
        static void Main(string[] args)
        {
            Student student = new Student { name = "John Doe", Age = 20 };
            Console.WriteLine($"Student name: {student.name}, Age: {student.Age}");
        }
    }
}

class person
{
   public string name;

}