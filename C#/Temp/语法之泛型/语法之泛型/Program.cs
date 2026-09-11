using System.Collections.Generic;

namespace Generic
{
    //T:类型参数，可以是任意类型，在使用时指定具体类型
    //泛型:带有“<>”的类型
    //分类:1.预定义的泛型类和方法，如Dictionary<TKey, TValue> 2.自定义的泛型类和方法
    class Program
    {
        static void Main(string[] args)
        {
            //泛型类
            List<int> list = new List<int>();
            list.Add(1);
            list.Add(2);
            list.Add(3);
            Console.WriteLine(list[0]);
            Console.WriteLine(list[1]);
            Console.WriteLine(list[2]);
            //泛型方法
            int a = 1;
            string b = "hello";
            Print<int>(a);//"<>"可以省略，编译器会自动推断类型
            Print(b);
        }
        //泛型方法
        public static void Print<T>(T value)
        {
            Console.WriteLine(value);
        }

        //T当参数用于指定方法的参数类型，T当返回值用来指定方法的返回值类型 ;接口约束：T : IComparable<T>，表示T必须实现IComparable<T>接口
        public static T GetDefault<T>()
        {
            //值类型不能为null，引用类型可以为null
            //default(T)表示获取类型T的默认值，如果T是值类型，则返回0；如果T是引用类型，则返回null
            return default(T);
        }

        static void Swap<T>(ref T a, ref T b)
        {
            T temp = a;//局部变量
            a = b;
            b = temp;
        }

        public class KllmClass<T>
        {
        }

        //泛型约束
        //class:引用约束；struct:值约束；new():无参构造函数/构造器约束；自定义类型 约束
        public static void Test1<T>() where T : class//约束T必须是引用类型
        {
            T tmp = default(T);//tmp的类型是T，初始值为null
        }
        public static T Test2<T>() where T : struct//约束T必须是值类型
        {
            return new T();//值类型都有隐式的无参构造函数，可以直接创建实例
        }

        public static void Test3<T>() where T : new()//约束T必须有无参构造函数
        {
            T tmp = new T();//创建T类型的实例，必须满足new()约束
        }


        public static void Test4<T>() where T : MyClass//约束T必须是MyClass或其派生类
        {
        }

        public interface IStudent1 { };
        public interface IStudent2 { };

        public static void Test5<T>() where T : MyClass ,IStudent1,IStudent2//接口约束可以有多个
        {
        }
        public static void Test6<T,S,U>() 
            where T : MyClass, IStudent1, IStudent2
            where S : struct
            where U : new()
        {
            //接口约束可以有多个
            //一个类型参数可以有多个约束，使用逗号分隔；
        }

        public class MyClass
    {
        public MyClass()
        {
        }
    }
}