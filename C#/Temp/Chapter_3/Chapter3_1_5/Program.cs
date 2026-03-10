using System;

namespace Chapter_3_1
{
    class Program//声明一个类
    {
        static void Main(string[] args)//特殊方法_入口方法
        {
            Console.WriteLine($"数字：{500}");
            Console.WriteLine($"数字：{500:c}");//货币
            Console.WriteLine($"数字：{500:f}");//十进制小数，默认两位
            Console.WriteLine($"数字：{500:f4}");//控制4位小数

        }
    }
}
