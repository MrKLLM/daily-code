
/// <summary>
/// 
/// 分部类：一个类的定义可以分散在多个文件中，每个文件都使用partial关键字声明该类。这些文件在编译时会被合并成一个完整的类。
/// 分布方法：分部方法是一种特殊的方法，可以在一个分部类中声明，但不需要在同一文件中实现。分部方法必须使用partial关键字声明，并且只能返回void类型。分部方法的实现可以在同一分部类的另一个文件中提供，也可以完全省略，如果没有提供实现，编译器会将调用该方法的代码忽略掉。

/// </summary>

public class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine();
    }
}

partial class Student
{
    public string Name { get; set; }
}

partial class MyClass
{
    //分部方法的声明
    partial void MyPartialMethod();
}
    
partial class MyClass
{
    //分部方法的实现
    partial void MyPartialMethod()
    {
        Console.WriteLine("这是分部方法的实现");
    }
}