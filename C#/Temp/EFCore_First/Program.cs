﻿//ORM框架(object-relational mapping)是一个用于在面向对象编程语言和关系型数据库之间进行数据转换的工具。它允许开发者使用面向对象的方式来操作数据库，而无需编写大量的SQL语句。ORM框架通过将数据库表映射为类，将表中的记录映射为对象，从而简化了数据访问和操作的过程。
//EFCore两种模式：Code First和Database First
//图书管理系统

//EFCore提供程序（dll)

//数据库连接字符串
//服务器名称：Data Source = (localdb)\MSSQLLocalDB;sever=;addr=
//数据库名称：database = book;initial catalog=;db=
//安全信息：tusted_connection=true;integrated security=true;uid=;user id=;pwd=;password=
//属性：MultipleActiveResultSets=true

string connString =@"Data Source=(localdb)\MSSQLLocalDB;database=efcoreDb;Integrated Security=true;";

//数据库上下文类（管道）
//数据库迁移（CodeFirst）add-migration(生成迁移代码）init-Mig(迁移名称）；update-database（执行到数据库）