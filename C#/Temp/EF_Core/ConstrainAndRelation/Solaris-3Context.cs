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
    public class Solaris_3Context:DbContext
    {
        

        public Solaris_3Context()
        {
        }

        public Solaris_3Context(DbContextOptions<Solaris_3Context> options) : base(options)
        {

        }
        //默认情况下属性名称Resonators就是表名
        public DbSet<Resonator> Resonators { get; set; }


        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer("Server=(localdb)\\MSSQLLocalDB;Initial Catalog=Solaris_3Db;Trusted_Connection=True;");
        }
    }

    
}