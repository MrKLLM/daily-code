using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;

namespace ConstrainAndRelation.Models
{
    public class Region
    {
        public int RegionId { get; set; }
        [StringLength(50,MinimumLength = 3,ErrorMessage = "Region name must be between 3 and 50 characters")]
        [Required]
        public string Name { get; set; }
        [Column(TypeName = "money")]
        public decimal Budget { get; set; }
        public DateTime CreatedAt { get; set; }
    }
}
