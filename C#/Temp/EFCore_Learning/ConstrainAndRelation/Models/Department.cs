using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ConstrainAndRelation.Models
{
    /// <summary>
    /// 系/部门实体
    /// ER图映射：对应 Departments 表
    /// 
    /// 涉及关系：
    ///   1. Department ↔ Instructor → 1对1（系主任是某个讲师）
    ///   2. Department ↔ Course     → 1对多（一个系有很多课程）
    /// </summary>
    public class Department
    {
        // ============================================
        // 主键
        // ============================================
        /// <summary>
        /// 系主键ID
        /// </summary>
        public int DepartmentId { get; set; }


        // ============================================
        // 普通属性
        // ============================================
        /// <summary>
        /// 系名称（3-50字符）
        /// </summary>
        [StringLength(50, MinimumLength = 3, ErrorMessage = "系名称必须在3-50个字符之间")]
        [Required(ErrorMessage = "系名称不能为空")]
        public string Name { get; set; }

        /// <summary>
        /// 预算金额（SQL Server money 类型）
        /// </summary>
        [Column(TypeName = "money")]
        public decimal Budget { get; set; }

        /// <summary>
        /// 系成立日期
        /// </summary>
        public DateTime StartDate { get; set; }


        // ============================================
        // 外键 + 导航属性（1对1：Department → Instructor）
        // ============================================
        /// <summary>
        /// 【外键（唯一）】该系负责人（讲师）的ID
        /// ER图证据：Departments 表里有 InstructorID 字段，且每个系只有一个负责人
        /// 虽然EF Core无法仅通过"外键"识别1对1，但我们在FluentAPI里会配置唯一索引
        /// </summary>
        public int InstructorId { get; set; }

        /// <summary>
        /// 【1对1导航属性】指向系主任（讲师）
        /// 用单个对象（不是ICollection），因为一个系只有一个负责人
        /// </summary>
        public virtual Instructor Instructor { get; set; }


        // ============================================
        // 导航属性（1对多：Department → Course）
        // ============================================
        /// <summary>
        /// 【1对多反向导航】该系开设的所有课程
        /// ER图证据：Departments.1 ↔ Courses.*
        /// 一的一方（Department）→ 用 ICollection<T> 反向导航
        /// </summary>
        public virtual ICollection<Course> Courses { get; set; }
    }
}