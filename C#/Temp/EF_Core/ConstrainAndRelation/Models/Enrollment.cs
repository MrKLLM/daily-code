using System;
using System.Collections.Generic;
using System.Text;

namespace ConstrainAndRelation.Models
{
    public enum GradeLevel
    {
        A,B,C,D,E
    }
    public class Enrollment
    {
        public int EnrollmentId { get; set; }
        public GradeLevel? Grade { get; set; }
    }
}
