//public_defs.h
//全局公共定义头文件
#include<string>

#pragma once

//最大数据量
#define MAX_PRIZE_WINNERS (100)

//是否在调试模式下
#define IS_DEBUG (1)

//公共错误信息，—1~—9保留给用户

#define PARA_ERROR (-11) //参数错误
#define FILE_ERROR (-12) //文件错误
#define MEMORY_ERROR (-13) //内存错误

//测试文件
#define TEST_FILE ("test_data.txt")

/**
 * @brief 奖项获奖者信息结构体
 */
struct PrizeWinner
{
    std::string name;//姓名
	long long id;//学号
    std::string sex;//性别
    std::string major;//专业
    std::string classes;//班级
    std::string competition;//比赛名称
    char competition_level;//比赛级别
    char prize_level;//奖项等级
};
