using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace ConstrainAndRelation.Models
{
    public class Instructor
    {
        public int InstructorId { get; set; }
        [StringLength(50,MinimumLength = 3,ErrorMessage = "Instructor name must be between 3 and 50 characters")]
        [Required]
        public string Name { get; set; }
        public DateTime HireDate { get; set; }
    }
}
