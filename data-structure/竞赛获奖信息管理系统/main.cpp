// main.cpp

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

#include "prize_winner.h"
#include "link.h"
#include "file.h"

int main(int argc, char** argv) {
	LinkedList list;
	InitList(list);
	
	ReadFromFile(TEST_FILE, list);
	
	int menu = 0;
	do {
		cout << "菜单\t 1：显示所有记录；2：添加获奖记录；3：删除指定记录；\n\t "
		"4：删除指定比赛记录；5：按学号查询；6：按比赛查询；\n\t "
		"7：清空链表数据；8：清空文件数据；9：保存所有记录；10:删除指定学生的学号 0：退出系统" << endl;
		
		cin >> menu;
		
		switch (menu) {
			case 1: {
			ShowAllMsg(list);
			break;
		}
			
			case 2: {
				cin.ignore(); // 清除输入缓冲区
				PrizeWinner winner;
				string item;
				
				getline(cin, winner.name, ',');
				getline(cin, item, ',');
				winner.id = stoll(item);
				getline(cin, winner.sex, ',');
				getline(cin, winner.major, ',');
				getline(cin, winner.classes, ',');
				getline(cin, winner.competition, ',');
				getline(cin, item, ',');
				winner.competition_level = item[0];
				getline(cin, item);
				winner.prize_level = item[0];
				
				InsertElement(list, winner);
				break;
			}
			
			case 3: {
				long long id;
				string competition;
				char prize_level;
				cin >> id >> competition >> prize_level;
				
				DelElement(list, id, competition, prize_level);
				break;
			}
			
			case 4: {
				string competition;
				cout << "请输入要删除的记录的比赛名称：" << endl;
				cin >> competition;
				
				DelCompetition(list, competition);
				break;
			}
			
			case 5: {
				long long id;
				cout << "请输入要查询的记录的学号：" << endl;
				cin >> id;
				
				FindMsgByStuNO(list, id);
				break;
			}
			
			case 6: {
				string competition;
				cout << "请输入要查询的记录的比赛名称：" << endl;
				cin >> competition;
				
				FindMsgByCompetition(list, competition);
				break;
			}
			
			case 7: {
				EmptyList(list);
				break;
			}
			
			case 8: {
				EmptyFileDate(TEST_FILE);
				break;
			}
			
			case 9: {
				SaveAllMsgTofile(list);
				break;
			}
			
			case 10:{
				long long id;
				cout << "请输入要删除的学生的学号：" << endl;
				cin >> id;
				DeleteMsgByStuNo(list,id);
				break;
			}

			case 0: {
				cout << "退出系统！" << endl;
				break;
			}
			
			default: {
				cout << "无效的选择，请重新输入。" << endl;
				break;
			}
		}
	} while (menu != 0);
	
	return 0;
}
