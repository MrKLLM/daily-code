namespace C_7_13
{
    /// <summary>
    /// this关键字
    /// 【1】用于引用当前实例的成员变量、方法或构造函数。在构造函数中，this关键字可以用来调用另一个构造函数，以避免代码重复。
    /// 【2】将对象作为参数传递给方法时，this关键字可以用来引用当前对象。
    /// </summary>
    internal class Program
    {
        static void Main(string[] args)
        {
            Person person = new Person("张三", 25);
            person.DisplayInfo();
           
        }
    }
     class Person
    {
        private string name;
        private int age;
        decimal salary;
        public decimal Salary
        {
            get { return salary; }
            set { salary = value; }
        }
        public Person(string name, int age)
        {
            //name = 方法参数
            //this.name = 当前对象的字段
            this.name = name; // 使用this关键字区分成员变量和参数
            this.age = age;   // 使用this关键字区分成员变量和参数
        }
        public void DisplayInfo()
        {
            Console.WriteLine($"姓名: {name}, 年龄: {age}");
            //通过以下方法将对象作为参数传递给方法
            Console.WriteLine("Taxes:{0:C}", Tax.CalculateTax(this));
            // 这里的this关键字引用当前对象，即当前正在执行这个方法的那个实例
            //等价于：Tax.CalculateTax(p)
            Console.WriteLine($"Taxes:{Tax.CalculateTax(this):C}");

            ///【:加总结】
            ///:C - 货币格式
            ///:D - 十进制格式
            ///:E - 科学计数法格式
            ///:F - 定点格式
            ///:G - 常规格式
            ///:N - 数字格式
            ///:P - 百分比格式
            ///:R - 区域性格式
            ///:X - 十六进制格式
            ///:0 - 占位符，表示输出的值将被格式化为默认格式
        }
    }

    class Tax
    {
        //计算税
        public static decimal CalculateTax(Person E)
        {
            return 0.08m * E.Salary ; // 假设税率为20%
        }
    }
}
