using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace ConstrainAndRelation.Models
{
    /// <summary>
    /// 课程实体
    /// ER图映射：对应 Courses 表
    /// 
    /// 涉及关系：
    ///   1. Course ↔ Department   → 多对一（课程属于某个系）
    ///   2. Course ↔ Instructor   → 多对多（课程可以由多个讲师教）
    ///   3. Course ↔ Resonator    → 多对多（通过 Enrollment 中间表，带Grade字段）
    /// </summary>
    public class Course
    {
        // ============================================
        // 主键
        // ============================================
        /// <summary>
        /// 课程主键ID
        /// </summary>
        public int CourseId { get; set; }


        // ============================================
        // 普通属性
        // ============================================
        /// <summary>
        /// 课程名称（3-50字符）
        /// </summary>
        [StringLength(50, MinimumLength = 3, ErrorMessage = "课程名称必须在3-50个字符之间")]
        [Required(ErrorMessage = "课程名称不能为空")]
        public string Title { get; set; }


        // ============================================
        // 外键 + 导航属性（1对多：Course → Department）
        // ============================================
        /// <summary>
        /// 【外键】该课程所属系的ID
        /// ER图证据：Courses 表里有 DepartmentID 字段
        /// 外键永远加在"多"的一方（多门课程属于同一个系）
        /// </summary>
        public int DepartmentId { get; set; }

        /// <summary>
        /// 【1对多导航属性】指向所属的系
        /// 多的一方（Course）→ 用单个对象
        /// </summary>
        public virtual Department Department { get; set; }


        // ============================================
        // 导航属性（多对多，带中间表 Enrollment）
        // ============================================
        /// <summary>
        /// 【多对多（显式中间表）】该课程的所有报名记录
        /// ER图证据：Courses.* ↔ Students.* 中间有 Enrollments 表（带 Grade 字段）
        /// 因为中间表有额外字段 Grade，所以必须显式定义 Enrollment 实体
        /// </summary>
        public virtual ICollection<Enrollment> Enrollments { get; set; }


        // ============================================
        // 导航属性（多对多，自动中间表）
        // ============================================
        /// <summary>
        /// 【多对多（自动中间表）】该课程的所有授课讲师
        /// ER图证据：Courses.* ↔ Instructors.* 中间有 CourseInstructor 表（仅两个FK）
        /// 中间表无额外字段 → EF Core 自动生成中间表
        /// </summary>
        public virtual ICollection<Instructor> Instructors { get; set; }
    }
}