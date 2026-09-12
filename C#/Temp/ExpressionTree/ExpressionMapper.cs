using System;
using System.Collections.Generic;
using System.Text;

namespace ExpressionTree
{
    public class ExpressionMapper<TIn,TOut>
    {
        public static Func<TIn, TOut>? _Func = null;

        static ExpressionMapper(){
            ParameterExpression parameterExp = Expression.Parameter(typeof(TIn), "p");//定义一个参数表达式，表示输入参数
            List<MemberBinding> memberBindingList = new List<MemberBinding>();//定义一个成员绑定列表，用于存储属性和字段的绑定
            //绑定属性
            foreach (var item in typeof(TOut).GetProperties())
            {
                MemberExpression member = Expression.Property(parameterExp, typeof(TIn).GetProperty(item.Name)!);//相当于 p => p.PropertyName
                MemberBinding binding = Expression.Bind(item, member);//创建一个成员绑定，表示将输入参数的属性绑定到输出类型的属性
                memberBindingList.Add(binding);
            }
            //绑定字段
            foreach (var item in typeof(TOut).GetFields())
            {
                MemberExpression member = Expression.Field(parameterExp, typeof(TIn).GetField(item.Name)!);
                MemberBinding binding = Expression.Bind(item, member);
                memberBindingList.Add(binding);
            }
            //创建新对象并初始化
            MemberInitExpression memberExpression = Expression.MemberInit(Expression.New(typeof(TOut)), memberBindingList.ToArray());//创建一个成员初始化表达式，表示创建一个新的输出类型对象，并将绑定的属性和字段初始化为输入参数的对应值
            var funcExp = Expression.Lambda<Func<TIn, TOut>>(memberExpression, parameterExp);//创建一个lambda表达式，表示将输入参数映射为输出类型对象

            _Func = funcExp.Compile();
        }
        static public TOut Mapper(TIn input)
        {
            if (_Func == null)
            {
                throw new InvalidOperationException("Mapping function is not initialized.");
            }
            return _Func(input);
        }
}
