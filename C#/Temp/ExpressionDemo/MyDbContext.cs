using ExpressionDemo.EF;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Text;

namespace ExpressionDemo
{
    public class MyDbContext : DbContext
    {
        //声明Dbset,代表数据库中的表
        public virtual DbSet<Student> Students { get; set; }
        //配置连接（这里用的是内存数据库）
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
                optionsBuilder.UseInMemoryDatabase("TestDb"); 
            }
        }
    }
}
