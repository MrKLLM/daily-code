// See https://aka.ms/new-console-template for more information

/*
 * 【1】C#程序或者DLL的源代码是一组，一种或多种类型声明
 ***类型是一种模板
 * 【2】对于可执行程序（.exe文件），类型声明中必须有一个包含Main方法的类
 * 【3】命名空间是把相关类型声明分组命名的方法，所以声明类型是都放在命名空间里面(命名空间用来管理类)
 * 【4】类是一种类型声明，包含属性、方法、事件、字段等成员
*/
Console.WriteLine("Hello, World!");

static void Main(string[] args)
{
    /*
    //预定义类型
    object obj;//是所有类型的基类
    uint ui = 10;//存储无符号整数
    decimal dec = 10.5M;//存储货币
    DateTime dt = DateTime.Now;//存储日期和时间
    //上面类型只是本名

    //自定义类型：用户自己定义的类型—》需要先声明再实例化——》复杂数据类型
    *类类型——class
    *结构类型—— struct
    *接口类型—— interface
    *枚举类型—— enum
    *委托类型—— delegate
    *数组类型—— array
    *
    *实例化—— new 关键字，分配内存空间
    *初始化—— 往里面放数据
    */
    Person p1;//声明变量,部分实例化
    Person p = new Person();//完整实例化
    p.Age = 25;
}


/*
 * 【1】本地变量--局部变量，生命周期只在当前方法内
 * 【2】字段--类的成员变量，存储类型或者类型实例相关的数据
 * 【3】属性--类的成员变量，可以有get和set方法，可以控制访问权限
 * 【4】方法--类的成员函数，可以有参数、返回值，可以调用其他方法
 * 【5】方法参数--临时变量，方法的输入，可以有默认值
 * 【6】数组元素--可以为本地变量或类型成员
 */
class Program
{
    int personAge;//字段
    Person person;//字段,引用类型,指向Person类的实例，只是分配了内存空间，还没有实例化
    Person person2 = new Person(); //字段,引用类型,完整实例化,new以后分配内存空间

    static void Main(string[] args)
    {
        int personAge = 1;
        //本地类型，局部变量，生命周期只在当前方法内
        //本地类型和参数使用前一定要初始化
    }
}
class Person
{
    public int Age { get; set; }
    public string Name { get; set; }
}