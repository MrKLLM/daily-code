﻿using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ConstrainAndRelation.Models
{
    /// <summary>
    /// 办公室分配实体
    /// ER图映射：对应 OfficeAssignments 表
    /// 
    /// 关系：Instructor ↔ OfficeAssignment → 1对1
    /// 
    /// EF Core识别1对1的关键特征：
    ///   依赖实体的【主键同时是被依赖实体的外键】
    ///   这里 OfficeAssignment 是依赖方（补充信息，离开Instructor无意义）
    /// </summary>
    public class OfficeAssignment
    {
        // ============================================
        // 主键 + 外键（合二为一 → 1对1的标志！）
        // ============================================
        /// <summary>
        /// 【主键 + 外键】该办公室分配所属的讲师ID
        /// 同时标记 [Key] 表示这是主键，
        /// EF Core 自动识别它也是 Instructor 的外键 → 1对1关系
        /// </summary>
        [Key]
        [ForeignKey("Instructor")]
        public int InstructorId { get; set; }


        // ============================================
        // 普通属性
        // ============================================
        /// <summary>
        /// 办公室位置（如：A栋301室）
        /// </summary>
        [StringLength(50, ErrorMessage = "办公室位置不能超过50个字符")]
        public string OfficeLocation { get; set; }


        // ============================================
        // 导航属性（指向被依赖方 Instructor）
        // ============================================
        /// <summary>
        /// 【1对1导航属性】指向所属的讲师
        /// 必须有这个导航属性，EF Core才能正确关联两端
        /// </summary>
        public virtual Instructor Instructor { get; set; }
    }
}