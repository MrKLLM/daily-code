﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿// ============================================================
// EF Core 迁移命令参考（CLI vs PM）
// -------------------------------------------------------------
// 生成迁移：
//   CLI: dotnet ef migrations add <迁移名称>
//   PM : Add-Migration <迁移名称>
//
// 更新数据库：
//   CLI: dotnet ef database update
//   PM : Update-Database
//
// 列出所有迁移：
//   CLI: dotnet ef migrations list
//   PM : Get-Migration
//
// 删除最新迁移（仅删除未应用的）：
//   CLI: dotnet ef migrations remove
//   PM : Remove-Migration
//
// 回滚到指定迁移：
//   CLI: dotnet ef database update <迁移名称>
//   PM : Update-Database <迁移名称>
//
// 删库（删除所有表和数据）：
//   CLI: dotnet ef database drop -f
//   PM : Drop-Database -Confirm:$false
//
// 生成 SQL 脚本（用于生产环境发布）：
//   CLI: dotnet ef migrations script
//   PM : Script-Migration
//
// 恢复种子数据（开发阶段推荐）：
//   CLI: dotnet ef database drop -f && dotnet ef database update
//   PM : Drop-Database -Force; Update-Database
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


            // ============================================
            // 数据播种（严格按依赖顺序！）
            // ============================================

            // ① Instructor —— 资深共鸣者/导师（根节点）
            modelBuilder.Entity<Instructor>().HasData(
                new { InstructorId = 1, Name = "散华", HireDate = new DateTime(2023, 5, 17) },
                new { InstructorId = 2, Name = "今汐", HireDate = new DateTime(2023, 5, 17) },
                new { InstructorId = 3, Name = "吟霖", HireDate = new DateTime(2024, 2, 1) }
            );

            // ② OfficeAssignment —— 驻点/据点（1对1，主键=外键）
            modelBuilder.Entity<OfficeAssignment>().HasData(
                new { InstructorId = 1, OfficeLocation = "今州" },
                new { InstructorId = 2, OfficeLocation = "今州" }
            );

            // ③ Department —— 势力/组织（系主任=该势力的资深共鸣者）
            modelBuilder.Entity<Department>().HasData(
                new { DepartmentId = 1, Name = "月影谷", Budget = 500000m, StartDate = new DateTime(2020, 1, 1), InstructorId = 1 },
                new { DepartmentId = 2, Name = "白缇教", Budget = 300000m, StartDate = new DateTime(2018, 6, 1), InstructorId = 2 }
            );

            // ④ Resonator —— 共鸣者（另一个根节点）
            // Type = 共鸣属性，Frequency = 共鸣频率(MHz)，Efficiency = 共鸣效率(%)
            modelBuilder.Entity<Resonator>().HasData(
                new { ResonatorId = 1, Name = "椿", Type = "堙灭", Frequency = 100, Efficiency = 95, EnrollmentDate = new DateTime(2025, 1, 1), SoftDeleted = false },
                new { ResonatorId = 2, Name = "守岸人", Type = "衍射", Frequency = 50, Efficiency = 88, EnrollmentDate = new DateTime(2025, 3, 15), SoftDeleted = false },
                new { ResonatorId = 3, Name = "秧秧", Type = "气动", Frequency = 75, Efficiency = 92, EnrollmentDate = new DateTime(2025, 6, 1), SoftDeleted = false },
                new { ResonatorId = 4, Name = "炽霞", Type = "热熔", Frequency = 200, Efficiency = 90, EnrollmentDate = new DateTime(2025, 9, 10), SoftDeleted = false },
                new { ResonatorId = 5, Name = "渊武", Type = "导电", Frequency = 150, Efficiency = 87, EnrollmentDate = new DateTime(2025, 11, 5), SoftDeleted = false },
                new { ResonatorId = 6, Name = "莉莉", Type = "衍射", Frequency = 80, Efficiency = 93, EnrollmentDate = new DateTime(2026, 1, 20), SoftDeleted = false }
            );

            // ⑤ Course —— 共鸣修行/委托任务（多对一，属于某个势力发布）
            modelBuilder.Entity<Course>().HasData(
                new { CourseId = 1, Title = "共鸣理论基础", DepartmentId = 1 },
                new { CourseId = 2, Title = "散华剑舞修行", DepartmentId = 1 },
                new { CourseId = 3, Title = "深渊区域探索委托", DepartmentId = 2 },
                new { CourseId = 4, Title = "执法实务训练", DepartmentId = 2 }
            );

            // ⑥ CourseInstructor 中间表 —— 资深共鸣者指导哪些修行
            modelBuilder.Entity<Instructor>()
                .HasMany(i => i.Courses)
                .WithMany(c => c.Instructors)
                .UsingEntity<Dictionary<string, object>>(
                    "CourseInstructor",
                    j => j.HasOne<Course>().WithMany().HasForeignKey("CoursesCourseId").OnDelete(DeleteBehavior.Restrict),
                    j => j.HasOne<Instructor>().WithMany().HasForeignKey("InstructorsInstructorId").OnDelete(DeleteBehavior.Restrict),
                    j => j.HasData(
                        new { CoursesCourseId = 1, InstructorsInstructorId = 1 },
                        new { CoursesCourseId = 1, InstructorsInstructorId = 2 },
                        new { CoursesCourseId = 2, InstructorsInstructorId = 1 },
                        new { CoursesCourseId = 3, InstructorsInstructorId = 2 },
                        new { CoursesCourseId = 4, InstructorsInstructorId = 3 }
                    )
                );

            // ⑦ Enrollment —— 共鸣者接受修行/委托（Grade = 任务评价等级）
            modelBuilder.Entity<Enrollment>().HasData(
                new { EnrollmentId = 1, ResonatorId = 1, CourseId = 1, Grade = GradeLevel.A },
                new { EnrollmentId = 2, ResonatorId = 1, CourseId = 2, Grade = GradeLevel.A },
                new { EnrollmentId = 3, ResonatorId = 2, CourseId = 1, Grade = GradeLevel.B },
                new { EnrollmentId = 4, ResonatorId = 3, CourseId = 2, Grade = GradeLevel.A },
                new { EnrollmentId = 5, ResonatorId = 4, CourseId = 3, Grade = GradeLevel.C },
                new { EnrollmentId = 6, ResonatorId = 5, CourseId = 4, Grade = GradeLevel.B },
                new { EnrollmentId = 7, ResonatorId = 6, CourseId = 1, Grade = (GradeLevel?)null }
            );


            // ---------- 2. Department ↔ Instructor 1对1 ----------
            // 约定无法自动识别（外键不在主键位置），必须用FluentAPI
            // Department有唯一的InstructorId → 一个系只有一个负责人
            modelBuilder.Entity<Department>()
                .HasOne(d => d.Instructor)
                .WithOne(i => i.Department)
                .HasForeignKey<Department>(d => d.InstructorId);

            // ---------- 4. Resonator 软删除 ----------
            // 全局查询过滤：自动排除 SoftDeleted = true 的记录
            modelBuilder.Entity<Resonator>()
                .HasQueryFilter(r => !r.SoftDeleted);
        }


        // ============================================
        // 软删除拦截：把 Remove 自动转成 UPDATE SoftDeleted = true
        // ============================================
        public override int SaveChanges()
        {
            foreach (var entry in ChangeTracker.Entries())
            {
                if (entry.State == EntityState.Deleted && entry.Entity is Resonator r)
                {
                    entry.State = EntityState.Modified;
                    r.SoftDeleted = true;
                }
            }
            return base.SaveChanges();
        }


        // ============================================
        // 数据库连接配置
        // ============================================
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            // 启用延迟加载
            optionsBuilder.UseLazyLoadingProxies();

            optionsBuilder.UseSqlServer(
                "Server=(localdb)\\MSSQLLocalDB;Initial Catalog=Solaris_3Db;Trusted_Connection=True;"
            );
        }
    }
}