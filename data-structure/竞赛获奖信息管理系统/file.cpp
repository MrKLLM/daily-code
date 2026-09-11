//file.cpp
//文件操作函数定义

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "file.h"
#include "link.h"
#include "public_defs.h"

using namespace std;

/**
 * @brief 从文件读取获奖信息
 * @param filename 文件名
 * @param list 链表
 * @return 成功返回true，失败返回false
 */
void ReadFromFile(const string& filename, LinkedList& list) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "无法打开文件: " << filename << endl;
        return;
    }

    string line;
    // 读取第一行标题
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        
        PrizeWinner winner;
        getline(ss, winner.name, ',');
        getline(ss, item, ',');
        winner.id = stoll(item);
        getline(ss, winner.sex, ',');
        getline(ss, winner.major, ',');
        getline(ss, winner.classes, ',');
        getline(ss, winner.competition, ',');
        getline(ss, item, ',');
        winner.competition_level = item[0];
        getline(ss, item);
        winner.prize_level = item[0];

        // 创建新节点并插入链表
        Node* newNode = CreateNode(winner);
        if(newNode != nullptr) {
            InsertNode(list, newNode);
        }
    }
    
    file.close();
    return;
}

/**
 * @brief 将获奖信息保存到文件
 * @param filename 文件名
 * @param list 链表
 * @return 成功返回true，失败返回false
 */
bool WriteToFile(const string& filename, const LinkedList& list) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "无法创建文件: " << filename << endl;
        return false;
    }

    // 写入标题行
    file << "学生姓名,学号,性别,专业,班级,比赛名称,赛事级别,获奖级别" << endl;

    Node* current = list.head->next;
    while (current != nullptr) {
        file << current->data.name << ","
             << current->data.id << ","
             << current->data.sex << ","
             << current->data.major << ","
             << current->data.classes << ","
             << current->data.competition << ","
             << current->data.competition_level << ","
             << current->data.prize_level << endl;
        current = current->next;
    }
    
    file.close();
    return true;
}

/**
 * @brief 清空文件内容
 * @param filename 文件名
 * @return 成功返回true，失败返回false
 */
bool EmptyFileDate(const string& filename) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cout << "无法清空文件: " << filename << endl;
        return false;
    }
    
    // 写入标题行
    file << "学生姓名,学号,性别,专业,班级,比赛名称,赛事级别,获奖级别" << endl;
    file.close();
    return true;
}
