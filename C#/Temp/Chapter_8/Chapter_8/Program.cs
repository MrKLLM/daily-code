
///类的继承
///【1】继承是面向对象编程的一个重要特性，它允许我们创建一个新类（子类/派生类）来继承一个现有类（父类/基类）的属性和方法。通过继承，子类可以重用父类的代码，同时也可以添加自己的特性和行为。
///【2】并非所有基类成员都可以被子类访问。静态构造函数、实力构造函数、终结器、私有成员和受保护成员都不能被子类访问。
///【3】子类不能删除父类的成员，但可以通过方法重写（override）来改变父类方法的行为。
///【4】所有类都直接或间接地继承自System.Object类，这意味着所有类都具有Object类的基本功能，如ToString()、Equals()和GetHashCode()方法。
///C＃只能继承一个类，但可以实现多个接口。这种单继承的限制使得C＃避免了多重继承带来的复杂性和潜在问题。

public class MyClass
{
    static void Main(string[] args)
    {
        Console.WriteLine();
    }
}

// 父类 Animal
public abstract class Animal//抽象类可以包含抽象方法
{
    // 虚方法，提供默认实现
    public virtual void MakeSound()
    {
        Console.WriteLine("The animal makes a sound");
    }

    // 抽象方法，没有实现，强制子类重写
    public abstract void Sleep();
}

// 继承自 Animal 的子类 Dog
public class Dog : Animal
{
    // 重写父类的虚方法 MakeSound
    public override void MakeSound()
    {
        Console.WriteLine("The dog barks: Woof! Woof!");
    }

    // 实现抽象方法 Sleep
    public override void Sleep()
    {
        Console.WriteLine("The dog is sleeping");
    }
}
public class Cat : Animal
{
    // 重写虚方法
    public override void MakeSound()
    {
        Console.WriteLine("The cat meows: Meow!");
    }

    // 实现抽象方法
    public override void Sleep()
    {
        Console.WriteLine("The cat sleeps in the sun.");
    }

    public void Purr()
    {
        base.Sleep();
    }
}

public class MyClass1
{
    public void 
}