﻿// ============================================================
// EF Core 迁移命令参考（CLI vs PM）
// ------------------------------------------------------------
// 生成迁移：
//   CLI: dotnet ef migrations add <迁移名称>
//   PM : Add-Migration <迁移名称>
//
// 更新数据库：
//   CLI: dotnet ef database update
//   PM : Update-Database
//
// 列出迁移：
//   CLI: dotnet ef migrations list
//   PM : Get-Migration
//
// 删除最新迁移：
//   CLI: dotnet ef migrations remove
//   PM : Remove-Migration
//
// 回滚到指定迁移：
//   CLI: dotnet ef database update <迁移名称>
//   PM : Update-Database <迁移名称>
//
// 注意：本项目使用 EF Core 10，PM 命令可能报
//       "不支持所指定的方法"，请优先使用 CLI 命令。
// ============================================================

using ConstrainAndRelation.Models;
using Microsoft.EntityFrameworkCore;

namespace ConstrainAndRelation
{
    /// <summary>
    /// 数据库上下文
    /// ER图来源：
    ///   - Instructors      (讲师)
    ///   - OfficeAssignments (办公室分配，1对1)
    ///   - Departments       (系/部门)
    ///   - Courses           (课程)
    ///   - Resonators        (谐振器/学生)
    ///   - Enrollments       (报名中间表，带Grade)
    /// </summary>
    public class Solaris_3Context : DbContext
    {
        public Solaris_3Context() { }

        public Solaris_3Context(DbContextOptions<Solaris_3Context> options) : base(options) { }


        // ============================================
        // DbSet 集合（对应数据库表）
        // ============================================
        // 默认情况下，DbSet 的属性名 = 数据库表名（复数形式）
        public DbSet<Instructor> Instructors { get; set; }
        public DbSet<OfficeAssignment> OfficeAssignments { get; set; }
        public DbSet<Department> Departments { get; set; }
        public DbSet<Course> Courses { get; set; }
        public DbSet<Resonator> Resonators { get; set; }
        public DbSet<Enrollment> Enrollments { get; set; }


        // ============================================
        // FluentAPI 配置（OnModelCreating）
        // ============================================
        /// <summary>
        /// 用于配置 EF Core 约定无法自动识别的关系
        /// 约定能识别的（如1对多、主键=外键的1对1、自动中间表）可以不用写
        /// </summary>
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // ---------- 1. Instructor ↔ Course 多对多 ----------
            // 约定可以识别（两边都有ICollection<对方>），
            // 这里手动配置只是为了指定中间表名字为 CourseInstructor（匹配ER图）
            modelBuilder.Entity<Instructor>()
                .HasMany(i => i.Courses)
                .WithMany(c => c.Instructors)
                .UsingEntity<Dictionary<string, object>>(
                    "CourseInstructor",
                    j => j.HasOne<Course>().WithMany().HasForeignKey("CoursesCourseId"),
                    j => j.HasOne<Instructor>().WithMany().HasForeignKey("InstructorsInstructorId")
                );

            // ---------- 2. Department ↔ Instructor 1对1 ----------
            // 约定无法自动识别（外键不在主键位置），必须用FluentAPI
            // Department有唯一的InstructorId → 一个系只有一个负责人
            modelBuilder.Entity<Department>()
                .HasOne(d => d.Instructor)
                .WithOne(i => i.Department)
                .HasForeignKey<Department>(d => d.InstructorId);

            // ---------- 3. Resonator.EnrollmentDate 默认值 ----------
            // 给谐振器/学生的登记日期默认设为今天
            modelBuilder.Entity<Resonator>()
                .Property(r => r.EnrollmentDate)
                .HasDefaultValueSql("GETDATE()");
        }


        // ============================================
        // 数据库连接配置
        // ============================================
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer(
                "Server=(localdb)\\MSSQLLocalDB;Initial Catalog=Solaris_3Db;Trusted_Connection=True;"
            );
        }
    }
}