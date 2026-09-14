using System;
using System.Collections.Generic;
using System.Text;

namespace KLLMSqlSeverDB
{
    //班级实体类--在数据库中表示一行数据
    public class StuClass
    {
        public int ClassId { get; set; } //班级编号
        public string ClassName { get; set; }//班级名称
    }
}
