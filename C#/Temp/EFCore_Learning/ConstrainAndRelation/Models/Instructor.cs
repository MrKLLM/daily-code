using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ConstrainAndRelation.Models
{
    /// <summary>
    /// 讲师实体
    /// ER图映射：对应 Instructors 表
    /// 
    /// 涉及关系：
    ///   1. Instructor ↔ OfficeAssignment  → 1对1（讲师的办公室分配）
    ///   2. Instructor ↔ Course            → 多对多（讲师可以教多门课程）
    ///   3. Instructor ↔ Department        → 1对1（讲师是某个系的负责人）
    /// </summary>
    public class Instructor
    {
        // ============================================
        // 主键
        // ============================================
        /// <summary>
        /// 讲师主键ID
        /// </summary>
        public int InstructorId { get; set; }


        // ============================================
        // 普通属性
        // ============================================
        /// <summary>
        /// 讲师姓名（3-50字符）
        /// </summary>
        [StringLength(50, MinimumLength = 3, ErrorMessage = "讲师姓名必须在3-50个字符之间")]
        [Required(ErrorMessage = "讲师姓名不能为空")]
        public string Name { get; set; }

        /// <summary>
        /// 入职日期
        /// </summary>
        public DateTime HireDate { get; set; }


        // ============================================
        // 导航属性
        // ============================================
        /// <summary>
        /// 【1对1】该讲师的办公室分配信息
        /// ER图证据：Instructors.1 ↔ OfficeAssignments.1
        /// OfficeAssignment的主键同时是Instructor的外键 → EF Core识别为1对1
        /// 注意：用单个对象（不是ICollection）！
        /// </summary>
        public virtual OfficeAssignment OfficeAssignment { get; set; }

        /// <summary>
        /// 【多对多】该讲师所教授的所有课程
        /// ER图证据：Instructors.* ↔ Courses.* 中间有 CourseInstructor 表
        /// EF Core 6+ 自动中间表：两边都加 ICollection<T> 即可
        /// </summary>
        public virtual ICollection<Course> Courses { get; set; }

        /// <summary>
        /// 【1对1】该讲师所负责的系（作为系主任）
        /// ER图证据：Departments 有 InstructorID 字段（唯一） → 一个系只有一个负责人
        /// 这里的 Department 是单个对象，因为一个讲师最多负责一个系
        /// </summary>
        public virtual Department Department { get; set; }
    }
}