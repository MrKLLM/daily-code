//Constrain(约束）和Relationship(关系）
//配置约束的方式有三种：
//1.按约定（通过默认配置）
//2.数据注释（通过属性配置）
//3.Fluent API（通过接口配置，最强大）

//一对一
//一对多
//多对多
//导航属性作用：1.建立数据库关系 2.关联查询

//057-数据库初始化数据(数据播种）
//058-数据查询与数据加载（关联查询）
//059-CRUD操作（增删改查）



using ConstrainAndRelation.Models;

using ConstrainAndRelation;
using Microsoft.EntityFrameworkCore;

#region 数据加载与查询

#region 获取一个表所有数据
// using (var db = new Solaris_3Context())
// {
//     var resonators = db.Resonators.ToList();
//     foreach (var r in resonators)
//     {
//         System.Console.WriteLine($"ResonatorId: {r.ResonatorId}, Name: {r.Name}, Type: {r.Type}, EnrollmentDate: {r.EnrollmentDate}");
//     }
// }
#endregion

#region 关闭跟踪查询，提高效率
// using (var db = new Solaris_3Context())
// {
//     // 关闭跟踪查询：AsNoTracking()
//     var resonators = db.Resonators.AsNoTracking().ToList();
//     foreach (var r in resonators)
//     {
//         System.Console.WriteLine($"ResonatorId: {r.ResonatorId}, Name: {r.Name}, Type: {r.Type}, EnrollmentDate: {r.EnrollmentDate}");
//     }
// }
#endregion

//数据加载分四种方式：预加载、延迟加载、显式加载、批量加载,默认不加载关联数据
#region 预加载（会加载所有数据进来）
//using (var db = new Solaris_3Context())
//{
//    //预加载通过两个方法实现：Include()和ThenInclude()
//    //Include()：加载直接关联的导航属性
//    //1.Include()：加载直接关联的导航属性
//    //2.ThenInclude()：加载间接关联的导航属性（多级关联）
//    var resonators = db.Resonators
//    .AsNoTracking()
//    .Include(r => r.Enrollments)
//    .ThenInclude(e => e.Course)
//    .ToList();
//    foreach (var r in resonators)
//    {
//        var enrollment = r.Enrollments.FirstOrDefault();
//        System.Console.WriteLine($"ResonatorId: {r.ResonatorId}, Name: {r.Name}, Type: {r.Type}, EnrollmentDate: {r.EnrollmentDate}" + $" Grade: {enrollment?.Grade}, Course: {enrollment?.Course?.Title}，这个学生选了多少门课：{r.Enrollments.Count()}");
//    }
//}
#endregion

#region 显示加载
//加载实体类需要的关系
//using (var db = new Solaris_3Context())
//{

//    var firstCourse = db.Courses.FirstOrDefault();
//    //根据查询到实体查询相关导航属性Collection方法是针对集合
//    db.Entry(firstCourse).Collection(c => c.Enrollments).Load();
//    //Reference方法是针对单个实体
//    db.Entry(firstCourse).Reference(c => c.Department).Load();
//    System.Console.WriteLine($"{firstCourse.Title},这门课有多少学生选： {firstCourse.Enrollments.Count()}, {firstCourse.Department?.Name}");
//}
#endregion

#region 选择加载（使用 ViewModel）

//using (var db = new Solaris_3Context())
//{
//    // ① 投影到 CourseViewModel（替代匿名类型）
//    var courseList = db.Courses.AsNoTracking().Select(c => new CourseViewModel
//    {
//        Title = c.Title,
//        DepartmentName = c.Department.Name
//    }).ToList();

//    // ② 传递给其他方法（匿名类型做不到这一点）
//    PrintCourses(courseList);

//    // ③ 序列化为 JSON（匿名类型不适合对外序列化）
//    string json = System.Text.Json.JsonSerializer.Serialize(courseList);
//    System.Console.WriteLine("\n=== JSON 输出 ===");
//    System.Console.WriteLine(json);
//}

static void PrintCourses(List<CourseViewModel> courses)
{
    System.Console.WriteLine("=== 方法内打印课程 ===");
    foreach (var c in courses)
    {
        System.Console.WriteLine($"课程: {c.Title}, 院系: {c.DepartmentName}");
    }
}
#endregion


#region 延迟加载
//配置方式
//1.安装Microsoft.EntityFrameworkCore.Proxies
//2.配置数据库上下文
//3.导航属性必须是虚属性

// using (var db = new Solaris_3Context())
// {
//        var resonators = db.Resonators.FirstOrDefault();
//        var enrollment = resonators.Enrollments.FirstOrDefault();
//        System.Console.WriteLine($"ResonatorId: {resonators.ResonatorId}, Name: {resonators.Name}, Type: {resonators.Type}, EnrollmentDate: {resonators.EnrollmentDate}" + $" Grade: {enrollment?.Grade}, Course: {enrollment?.Course?.Title}");
// }

#endregion

#endregion

#region CRUD
using (var db = new Solaris_3Context())
{
    //增
    // var newResonator = new Resonator
    // {
    //     Name = "爱弥斯",
    //     Type = "热熔",
    //     EnrollmentDate = DateTime.Now
    // };
    // db.Resonators.Add(newResonator);//在内存中添加
    // db.AddRange(newResonator);//在内存中添加多个实体

    //改
    // var firstResonator = db.Resonators.Find(4);
    // firstResonator.Name = "爱弥斯2";
    
    //删（默认是级联删除-关联的实体也会被删除）
    var Res2 = db.Resonators.FirstOrDefault(s => s.ResonatorId == 5);
    // db.Resonators.Remove(Res);//在内存中删除
    Res2.SoftDeleted = true;//软删除
    db.Resonators.Update(Res2);

    db.SaveChanges();//提交到数据库
}
#endregion

class CourseViewModel
{
    public string Title { get; set; }
    public string DepartmentName { get; set; }
}
