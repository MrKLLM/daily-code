using ExpressionDemo.LinqToSql;
using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using System.Text;

namespace ExpressionDemo
{
    /// <summary>
    /// 条件访问器
    /// 
    /// 表达式树的永久性：想修改一个表达式树，只能创建一个新的表达式树，不能修改原来的表达式树。
    /// </summary>
    public class ConditionVisitor:ExpressionVisitor
    {
        private Stack<string> _stringStack = new Stack<string>();

        //返回栈里面的字符串
        public string GetConditionString()
        {
            var arr = this._stringStack.ToArray().Reverse();
            string conditon = string.Concat(arr);
            this._stringStack.Clear();
            return conditon;

            //((([Age] > 40) AND ([Id] > 1)) AND  [Address] LIKE N'%海%' )
        }

        //二元表达式
        protected override Expression VisitBinary(BinaryExpression node)
        {
            _stringStack.Push("(");
            Visit(node.Left);//解析左边，递归调用
            _stringStack.Push(" " + node.NodeType.ToOperator() + " ");
            Visit(node.Right);//解析右边，递归调用
            _stringStack.Push(")");
            return node;
        }
        //成员表达式
        protected override Expression VisitMember(MemberExpression node)
        {
            _stringStack.Push("[" + node.Member.Name + "]");
             return node;
        }
        //常量表达式
        protected override Expression VisitConstant(ConstantExpression node)
        {
            Type type = node.Value.GetType();
            if(type == typeof(string) || type == typeof(DateTime))
            {
                _stringStack.Push($"'{node.Value}'");
            }
            else
            {
                _stringStack.Push(node.Value.ToString());
            }
            return node;
        }
        //方法表达式
        //s.Address.Contains("海")
        protected override Expression VisitMethodCall(MethodCallExpression node)
        {
            Visit(node.Object);//左边：被调用方法所属的实例（谁在调用这个方法），返回是成员表达式-->跳转到VisitMember方法
            Visit(node.Arguments[0]);//右边：传给方法的参数，返回是常量表达式-->跳转到VisitConstant方法

            //获取入栈数据，为方法解析做参数（参数和字段名）

            string right = _stringStack.Pop();//'海'
            string left = _stringStack.Pop();//Address
            switch(node.Method.Name)
            {
                case "Contains":
                    _stringStack.Push($" {left} LIKE N'%{right.Trim('\'')}%' ");
                    break;
                case "StartsWith":
                    _stringStack.Push($" {left} LIKE N'{right.Trim('\'')}%' ");
                    break;
                case "EndsWith":
                    _stringStack.Push($" {left} LIKE N'%{right.Trim('\'')}' ");
                    break;
                default:
                    throw new NotSupportedException($"不支持的方法: {node.Method.Name}");
            }

            return node;
        }
    }
}
