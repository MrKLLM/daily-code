using ExpressionDemo.EF;
using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq.Expressions;
using System.Text;

namespace ExpressionDemo
{
    /// 
    /// ExpressionTree使用场景一AutoMapper自动映射框架
    /// 
    ///序列化反序列化
    ///反射
    ///
    ///ExpressionTree使用场景二
    ///EF框架类似功能--SQL语句解析(条件)
    ///
    ///DbFirst--数据库优先模式
    ///1.手动拼接
    ///2.自动拼接
    ///3.手动＋自动拼接
    ///
    class Program
    {
        static void Main(string[] args)
        {
            //拼接SQL语句条件
            {
                
                //1.实例化BdContext
                using var db = new MyDbContext();
                db.Students.Add(new Student { Name = "卡提西娅", Age = 34, Id = 1 ,Address = "黎那汐塔"});
                db.Students.Add(new Student { Name = "椿", Age = 3000, Id = 2 ,Address = "黑海岸"});
                db.Students.Add(new Student { Name = "莫宁", Age = 45, Id = 3 ,Address = "拉海洛"});
                db.Students.Add(new Student { Name = "锁暝", Age = 220, Id = 4 ,Address = "梦州"});
                db.SaveChanges();

                //2.查询数据
                var elders = db.Students.Where(s => s.Age > 40 && s.Id > 1 && s.Address.Contains("海")).ToList();

                Expression<Func<Student, bool>> func = s => s.Age > 40 && s.Id > 1 && s.Address.Contains("海");

                Console.WriteLine(func);
                Console.WriteLine(elders);
                Console.WriteLine("年龄大于40的共鸣者且Id大于1且家乡包含'海'：");
                foreach (var item in elders)
                {
                    Console.WriteLine($"姓名: {item.Name}, 年龄: {item.Age}，家乡: {item.Address}");

                }

                //ExpressionVisitor
                CustomVisitor visitor = new CustomVisitor();
                visitor.Visit(func);

                ConditionVisitor conditionVisitor = new ConditionVisitor();
                conditionVisitor.Visit(func);
                Console.WriteLine(conditionVisitor.GetConditionString());
            }


            Console.ReadLine();
            

        }
    }
    public class  CustomVisitor:ExpressionVisitor
    {
        
        public override Expression? Visit(Expression? node)
        {
            return base.Visit(node);
        }
        protected override Expression? VisitBinary(BinaryExpression? node)
        {
            return base.VisitBinary(node);
        }
        protected override Expression? VisitMethodCall(MethodCallExpression? node)
        {
            return base.VisitMethodCall(node);
        }
    }
}

