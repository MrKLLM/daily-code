using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace ConstrainAndRelation.Models
{
    public class Course
    {
        public int CourseId { get; set; }
        [StringLength(50,MinimumLength = 3,ErrorMessage = "Course name must be between 3 and 50 characters")]
               [Required]
        public string Name { get; set; }
    }
}
