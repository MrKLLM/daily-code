using System.Linq.Expressions;

namespace ExpressionTree
{
    public class ExpressionMapper<TIn,TOut>
    {
        public static Func<TIn, TOut>? _Func = null;

        static ExpressionMapper(){
            ParameterExpression parameterExp = Expression.Parameter(typeof(TIn), "p");//定义一个参数表达式，表示输入参数
            List<MemberBinding> memberBinding = new List<MemberBinding>();
            //绑定属性
            foreach (var item in typeof(TOut).GetProperties())
            {
                MemberExpression member = Expression.Property(parameterExp, typeof(TIn).GetProperty(item.Name)!);

            }
        }
    }
}