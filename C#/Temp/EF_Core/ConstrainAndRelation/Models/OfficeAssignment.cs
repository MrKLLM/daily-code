using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace ConstrainAndRelation.Models
{
    public class OfficeAssignment
    {
        [Key]
        public int InstructorId { get; set; }
        [StringLength(50)]
        public string OfficeLocation { get; set; }
    }
}
