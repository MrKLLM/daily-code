#include<iostream>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

struct Student{
    int Num;
    int Score;
    Student* Next;
    Student(int a,int b):Num(a),Score(b),Next(NULL){}
};

int main() {
    Student* head  = NULL;
    Student* tail  = NULL;
    
    for (size_t i = 0; i < 3; i++)
    {
        int tmp1,tmp2;
        cin >> tmp1 >> tmp2;
        Student* newStudent = new Student(tmp1,tmp2);//利用构造函数

        //连接节点
        if (head == NULL)
        {
            head = newStudent;
            tail = newStudent;    
            /* code */
        }
        else
        {
            tail->Next = newStudent;
            tail = newStudent;
            /* code */
        }
    }
    Student* p = new Student(0,0);
    p = head;
    for (size_t i = 0; i < 3; i++)
    {
        
        cout << "[num=" << p->Num << ",score=" << p->Score << "]" << endl; 
        p=p->Next;   
        //std::cout << std::format("[num={},score={}]", num, score) << std::endl;
        /* code */
    }
    
    /* code */
    
    
	return 0;
}
