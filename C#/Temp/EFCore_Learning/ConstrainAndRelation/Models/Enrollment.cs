using System;
using System.Collections.Generic;

namespace ConstrainAndRelation.Models
{
    /// <summary>
    /// 成绩等级枚举
    /// </summary>
    public enum GradeLevel
    {
        A, B, C, D, E
    }

    /// <summary>
    /// 报名/登记中间表实体
    /// ER图映射：对应 Enrollments 表
    /// 
    /// 作用：Resonator ↔ Course 的多对多关系的显式中间表
    /// 
    /// 为什么需要显式定义而不用EF Core自动中间表？
    ///   因为中间表有【额外业务字段 Grade（成绩）】
    ///   EF Core自动中间表只能存储两个外键，无法扩展
    /// 
    /// ER图证据：Enrollments 表有 EnrollmentID, CourseID, StudentID, Grade
    /// </summary>
    public class Enrollment
    {
        // ============================================
        // 主键
        // ============================================
        /// <summary>
        /// 报名记录主键ID
        /// </summary>
        public int EnrollmentId { get; set; }


        // ============================================
        // 额外业务字段（这就是显式中间表存在的原因！）
        // ============================================
        /// <summary>
        /// 成绩（可空，表示尚未评定）
        /// EF Core会把枚举存为 int（A=0, B=1, ...）
        /// </summary>
        public GradeLevel? Grade { get; set; }


        // ============================================
        // 两个外键 + 两个导航属性
        // ============================================
        /// <summary>
        /// 【外键】报名的谐振器/学生ID
        /// ER图对应：Enrollments.StudentID（这里Student改名为Resonator）
        /// </summary>
        public int ResonatorId { get; set; }

        /// <summary>
        /// 【外键】报名的课程ID
        /// ER图对应：Enrollments.CourseID
        /// </summary>
        public int CourseId { get; set; }

        /// <summary>
        /// 【导航属性】指向报名的谐振器/学生
        /// </summary>
        public virtual Resonator Resonator { get; set; }

        /// <summary>
        /// 【导航属性】指向报名的课程
        /// </summary>
        public virtual Course Course { get; set; }
    }
}