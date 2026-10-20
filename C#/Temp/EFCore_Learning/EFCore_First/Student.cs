using System;
using System.Collections.Generic;
using System.Text;

namespace EFCore_First
{
    class Database
    {
        public Student Students { get; set; }
    }
    public class Student
    {
        public int StuId { get; set; }
        public string Name { get; set; }
    }
}
