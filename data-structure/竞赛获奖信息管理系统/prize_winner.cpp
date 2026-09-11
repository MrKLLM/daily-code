// prize_winner.cpp
//业务逻辑实现

#include<iostream>
#include<fstream>
#include<string>
#include "public_defs.h"
#include "link.h"
#include "file.h"
#include "prize_winner.h"
/**
 * @brief 显示链表中所有节点的信息
 * @param list 要显示的链表
 */
void ShowAllMsg(const LinkedList& list){
    Node* p = new Node();
    if (list.head->next == nullptr)
    {
        cout<<"链表为空！"<<endl;
        return;
    }

    p = list.head->next;
    while (p != nullptr)
    {
       cout << p->data.name << "," << p->data.id << "," << p->data.sex << "," << p->data.major << "," << p->data.classes << "," << p->data.competition << "," << p->data.competition_level << "," << p->data.prize_level << endl;
       p = p->next;
    }
}
/**
 * @brief 在链表末尾插入一个新的节点
 * @param list 要插入节点的链表
 * @param winner 要插入的数据（PrizeWinner）
 */
// prize_winner.cpp 中添加
void InsertElement(LinkedList& list, const PrizeWinner& winner) {
	Node* newNode = CreateNode(winner);
	if (newNode != nullptr) {
		InsertNode(list, newNode);
	}
} 
/**
 * @brief 删除链表中满足条件的节点
 * @param list 要删除节点的链表
 * @param id 要删除的节点的学号
 * @param competition 要删除的节点的比赛名称
 * @param prize_level 要删除的节点的奖项等级
 */
void DelElement(LinkedList& list, long long id,std::string competition,char prize_level){
    PrizeWinner p ;
    p.id = id;
    p.competition = competition;
    p.prize_level = prize_level;
    del_by_id_comp_lvl(list,p);
};

/**
 * @brief 删除链表中满足条件的节点
 * @param list 要删除节点的链表
 * @param competition 要删除的节点的比赛名称
 */
void DelCompetition(LinkedList& list,std::string competition){
    Node* p = list.head->next;
    Node* pre  = nullptr;
    while (p != nullptr)
    {
        if (p->data.competition == competition)
        {
            if (pre == nullptr)//头节点
            {
                list.head = p->next;
            }
            else//其他节点和尾节点
            {
                pre->next = p->next;
                
            }
            //无论是不是头节点，尾节点都要更新，所以缩进层级浅一点
            if (p == list.tail)
            {
                list.tail = pre;             
            }
            Node* tmp = p;
            p = p->next;
            if (tmp != nullptr)
            {
                delete tmp;
                tmp = nullptr;
            }
            list.size--;
        }else
        {               
            pre = p;
            p = p->next;    
        }
        
    }
};

/**
 * @brief 查找链表中满足条件的节点并显示其信息
 * @param list 要查找节点的链表
 * @param id 要查找的节点的学号
 */
void FindMsgByStuNO(LinkedList& list,long long id){
    Node* current = list.head->next;
    while (current != nullptr)
    {
        if (current->data.id == id)
        {
            cout << current->data.name << "," << current->data.id << "," << current->data.sex << "," << current->data.major << "," << current->data.classes << "," << current->data.competition << "," << current->data.competition_level << "," << current->data.prize_level << endl;
        }
        current = current->next;
    }
};

/**
 * @brief 查找链表中满足条件的节点并显示其信息
 * @param list 要查找节点的链表
 * @param competition 要查找的节点的比赛名称
 */
void FindMsgByCompetition(LinkedList& list,std::string competition){
    Node* current = list.head->next;
    while (current != nullptr)
    {
        if (current->data.competition == competition)
        {
            cout << current->data.name << "," << current->data.id << "," << current->data.sex << "," << current->data.major << "," << current->data.classes << "," << current->data.competition << "," << current->data.competition_level << "," << current->data.prize_level << endl;
        }
        current = current->next;
    }
};

/**
 * @brief 清空链表
 * @param list 要清空的链表
 */
void EmptyList(LinkedList& list){
    Node* current = list.head->next;
    while (current != nullptr)
    {
        Node* tmp = current;
        current = current->next;
        delete tmp;
    }
    list.head->next = nullptr;
    list.tail = list.head; 
    list.size = 0;
};

/**
 * @brief 保存所有信息获奖信息
 * @param list 要保存信息的链表
 */
void SaveAllMsgTofile(const LinkedList& list){
    WriteToFile(TEST_FILE, list);
};

/**
 * @brief 删除指定学生所有获奖信息
 * @param list 要查找节点的链表
 * @param id 某人学号
 */
void DeleteMsgByStuNo(LinkedList& list,long long id){
	if(list.head == nullptr){
		return;
	}
	
    Node* curr = list.head->next;
    Node* pre = list.head;
    while (curr != nullptr && curr->data.id != id)
    {
        pre = curr;
        curr = curr->next;
    }
	
	if(curr == nullptr)
	{
		return;
	}
	//删头节点
	if(pre == list.head)
	{
		list.head->next = curr->next;
	}
	else//中或尾
    {
        pre->next = curr->next;
    }
    //尾时
	if(curr == list.tail){
		list.tail = pre;
	}
	delete curr;
};
