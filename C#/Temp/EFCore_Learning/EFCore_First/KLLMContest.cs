﻿using Microsoft.EntityFrameworkCore;

namespace EFCore_First
{
    //可以把上下文类理解为数据库的一个抽象，EFCore通过上下文类来操作数据库。上下文类继承自DbContext类，DbContext类是EFCore中最重要的类之一，它提供了与数据库交互的基本功能。
    public class KLLMContext:DbContext
    {
        //主要是框架再用，有时用户也会用到
        public KLLMContext() 
        {

        }

        public KLLMContext(DbContextOptions<KLLMContext> options):base(options)
        {

        }

        public DbSet<Book> Book { get; set; }

        //配置上下文类
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            string connString = @"Data Source=(localdb)\MSSQLLocalDB;database=efcoreDb;Integrated Security=true;";
            if (!optionsBuilder.IsConfigured)
            {
                optionsBuilder.UseSqlServer(connString);
            }
        }
    }
}