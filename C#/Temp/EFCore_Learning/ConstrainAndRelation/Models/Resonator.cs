using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ConstrainAndRelation
{
    /// <summary>
    /// 谐振器实体 —— 同时承担两个角色：
    ///   1. 物理谐振器：具有类型、频率、效率等物理属性
    ///   2. ER图中 Students 表的角色：需要 EnrollmentDate 表示入学/登记时间
    /// 
    /// ER图映射：对应 Students 表
    /// 关系：Resonator ↔ Enrollment (多对多，通过Enrollment中间表)
    /// </summary>
    public class Resonator
    {
        // ============================================
        // 主键
        // ============================================
        /// <summary>
        /// 谐振器主键ID
        /// EF Core约定：类名+Id（或ID）自动识别为主键
        /// </summary>
        public int ResonatorId { get; set; }


        // ============================================
        // 物理谐振器属性
        // ============================================
        /// <summary>
        /// 谐振器名称（映射到数据库列 ResonatorName）
        /// </summary>
        [StringLength(50, ErrorMessage = "谐振器名称不能超过50个字符")]
        [Column("ResonatorName")]
        [Required(ErrorMessage = "谐振器名称不能为空")]
        public string Name { get; set; }

        /// <summary>
        /// 谐振器类型（如：石英、陶瓷、SAW等）
        /// </summary>
        [StringLength(30, ErrorMessage = "类型名称不能超过30个字符")]
        public string Type { get; set; }

        /// <summary>
        /// 工作频率（单位：MHz）
        /// </summary>
        [Range(1, 100000, ErrorMessage = "频率必须在1-100000 MHz之间")]
        public int Frequency { get; set; }

        /// <summary>
        /// 额定功率（单位：mW）
        /// [NotMapped] = 不映射到数据库，仅内存中计算使用
        /// </summary>
        [NotMapped]
        public int Power { get; set; }

        /// <summary>
        /// 谐振效率（百分比 0-100）
        /// </summary>
        [Range(0, 100, ErrorMessage = "效率必须在0-100之间")]
        public int Efficiency { get; set; }


        // ============================================
        // ER图 Students 角色属性
        // ============================================
        /// <summary>
        /// 登记/入学日期
        /// ER图对应：Students.EnrollmentDate
        /// </summary>
        public DateTime EnrollmentDate { get; set; }


        // ============================================
        // 导航属性
        // ============================================
        /// <summary>
        /// 该谐振器/学生所报名的所有登记记录
        /// 对应ER图：Students ↔ Enrollments 多对多关系的反向导航
        /// EF Core约定：ICollection<T> 表示集合导航属性
        /// 命名规范：用复数形式（Enrollments）
        /// </summary>
        public virtual ICollection<Enrollment> Enrollments { get; set; }
    }
}