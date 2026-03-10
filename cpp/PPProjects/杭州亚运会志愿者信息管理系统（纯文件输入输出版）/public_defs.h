#pragma once

#ifndef NULL
#define NULL (0)
#endif

// 定义 byte 类型
typedef unsigned char byte;

// 最大数据量
#define MAX_COUNT (300)

// 调试开关
#define IS_DEBUG (0)

// 公共错误码
#define PARA_IS_NULL (-11)   // 参数为空
#define FILE_OPEN_ERROR (-12) // 文件打开失败

/**
 * 志愿者结构体（严格遵循实验指导书定义）
 */
struct Volunteer {
	int number;        // 编号（int类型）
	char name[20];     // 姓名
	int age;           // 年龄
	char gender;       // 性别（F/M，单个字符）
	char language[10]; // 掌握语言
	int grade;      // 成绩
};
