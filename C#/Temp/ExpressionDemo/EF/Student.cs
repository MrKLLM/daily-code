using System;
using System.Collections.Generic;
using System.Text;

namespace ExpressionDemo.EF
{
    public class Student
    {
        public int Id { get; set; }
        public required string Name { get; set; }
        public int Age { get; set; }
        public string? Address { get; set; } = null;
    }
}
