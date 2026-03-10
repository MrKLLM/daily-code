using System;

namespace Chapter_3_1
{

    //块只能写在方法里面
    class Program//声明一个类
    {
        static void Main(string[] args)//特殊方法_入口方法
        {
            string str = "你好";
            Console.WriteLine("Hello, World!");
            Console.WriteLine("{0}, {1}","你好,","世界!");
            Console.WriteLine("{0}",str);
            Console.WriteLine($"Hello {str}, World{"世界"}{123}");//插值字符串（C#6.0）,方便阅读
        }
    }
}
