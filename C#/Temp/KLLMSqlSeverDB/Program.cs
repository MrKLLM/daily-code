

using System.Data.SqlClient;

namespace KLLMSqlSeverDB
{
    class Program
    {
        //链接字符串--链接数据库用
        public static readonly string connString = @"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=StuManeger;Integrated Security=True;Connect Timeout=30;Encrypt=False";
        static void Main(string[] args)
        {
            //定义sql语句
            string sql = "select ClassName from StuClass where ClassName=N'农楚楚班'";
            //链接sql语句
            using (SqlConnection conn = new SqlConnection(connString)) //连接数据库，确保自动释放
            {
                using (SqlCommand cmd = new SqlCommand(sql, conn) { CommandTimeout = 30 })
                {
                    conn.Open();//打开链接
                    object res = cmd.ExecuteScalar();

                    //展示数据
                    Console.WriteLine("班级名称：" + (res.ToString()));
                }
            }

            Console.Read();
        }
    }
}