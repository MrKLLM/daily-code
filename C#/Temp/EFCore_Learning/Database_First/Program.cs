//Scaffold-Dbcontext "Server=(localdb)\MSSQLLocalDB;Database=AdventureWorksLT2025;trusted_connection=True;MultipleActiveResultSets=True;" Microsoft.EntityFrameworkCore.SqlServer -Context KLLMDbContext -OutputDir Models -contextdir Data -Table Address,Product -DataAnnotations -Force


//-Context KLLMDbContext,上下文类名称
//-OutputDir Models,模型类输出目录
//-contextdir Data,上下文类输出目录

//-Table Address,Product,指定生成的表名
//DataAnnotations,生成数据注解属性
//-Force,强制生成
public partial class Program { public static void Main() { } }