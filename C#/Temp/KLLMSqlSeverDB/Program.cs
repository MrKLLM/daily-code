

using System.Data;
using System.Data.SqlClient;
using System.Collections.Generic;
using System.Xml.Linq;

namespace KLLMSqlSeverDB
{
    class Program
    {
        #region 读取单个对象
        /*
        public static readonly string connString = @"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=StuManeger;Integrated Security=True;Connect Timeout=30;Encrypt=False";
        static void Main(string[] args)
        {
            //定义sql语句
            string sql = "select ClassName from StuClass where ClassName=N'农楚楚班'";

            //链接sql语句
            SqlConnection conn = new SqlConnection(connString); //连接数据库
            SqlCommand cmd = new SqlCommand(sql, conn);

            conn.Open();//打开链接
            object res = cmd.ExecuteScalar();
            conn.Close();
            //展示数据
            Console.WriteLine("班级名称：" + (res.ToString()));
            Console.Read();
            */
        #endregion


        #region 读取多个对象
        //链接字符串--链接数据库用
        public static readonly string connString = @"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=StuManeger;Integrated Security=True;Connect Timeout=30;Encrypt=False";
        static void Main(string[] args)
        {

            //定义sql语句
            string sql = "select ClassId,ClassName from StuClass";
            
            //链接ADO.NET做数据查询
            SqlConnection conn = new SqlConnection(connString); //连接数据库
            SqlCommand cmd = new SqlCommand(sql, conn);
            List<StuClass> stuList = new List<StuClass>();
            conn.Open();
            //检测并自动关闭数据库链接
            SqlDataReader reader = cmd.ExecuteReader(CommandBehavior.CloseConnection);
            //解析数据

            while (reader.Read())
            {
                stuList.Add(new StuClass()
                {
                    ClassId = reader.GetInt32(reader.GetOrdinal("ClassId")),
                    ClassName = reader.GetString(reader.GetOrdinal("ClassName"))
                });
            }
            reader.Close();
            //展示数据

            foreach (var stu in stuList)
            {
                Console.WriteLine("班级名称：" + stu.ClassId + "，班级名称：" + stu.ClassName);
                
            }
            Console.Read();
        }
        #endregion
    }
}