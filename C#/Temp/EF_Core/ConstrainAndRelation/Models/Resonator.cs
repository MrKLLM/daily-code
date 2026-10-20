using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text;

namespace ConstrainAndRelation
{
    //[Table("Resonator2")]
    public class Resonator
    {
        //一个表第一个字段含有Id或ID，EF Core会自动将其作为主键处理
        //[Key]
        public int ResonatorId { get; set; }
        [StringLength(50)]
        [Column("ResonatorName")]
        [Required]
        public string Name { get; set; }
        public string Type { get; set; }
        public int Frequency { get; set; }
        [NotMapped]
        public int Power { get; set; }
        public int Efficiency { get; set; }
        public DateTime EnrollmentDate { get; set; }
    }
}
