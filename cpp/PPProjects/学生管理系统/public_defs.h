#pragma once


#ifndef NULL    //判断这个宏是否被定义
#define NULL  (0)
#endif

/*
typedef 关键字
C/C++ 中的关键字，用于为已有数据类型创建别名（不是定义新类型，只是给现有类型起 “外号”），目的是提升代码可读性、简化复杂类型书写。
*/
// 定义 byte 类型
typedef unsigned char byte;

// 最大数据量
#define MAX_COUNT    (300)

// 是否在调试状态，调试状态输出调试信息，正式运行不输出
#define    IS_DEBUG    (1)

// 公共错误信息,-1~ -9 保留给用户定义
// 参数为NULL
#define PARA_IS_NULL    (-11)
#define FILE_OPEN_ERROR    (-13)

/*
定义不同错误码的核心目的是 精准区分错误类型、方便调试和针对性处理错误，
如果都用同一个错误码，会导致 “不知道哪里错了、没法针对性解决问题”
*/

/**
 * 学生结构体
 */
struct  Student
{
	// 学号
	char id[15];
	
	// 姓名
	char name[20];
	
	// 年龄
	int age;
	
	// 性别
	char sex;
	
	// 专业
	char major[20];
	
};
