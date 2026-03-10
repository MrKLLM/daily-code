#pragma once
#include "public_defs.h"
#include "link.h"
#include <string>
using namespace std;

/**
 * 志愿者信息转为字符串（空格分隔，符合实验要求）
 * @param volunteer 志愿者结构体指针
 * @return 格式化字符串
 */
string Volun2Str(const Volunteer* volunteer);

/**
 * 将链表所有信息写入out.txt（覆盖原有内容）
 * @param head 链表头节点
 * @param fileName 输出文件名（固定为out.txt）
 * @return 写入的记录数；负数=错误码
 */
int output(Node* const head, const char* fileName);

/**
 * 将单个志愿者信息写入out.txt（用于查找功能）
 * @param volun 目标志愿者指针
 * @param fileName 输出文件名（固定为out.txt）
 * @return 0=成功；负数=错误码
 */
int output(const Volunteer* volun, const char* fileName);
