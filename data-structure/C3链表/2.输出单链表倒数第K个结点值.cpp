#include<iostream>
using namespace std;


struct Node{
    int Num;
    Node* Next;

    //构造函数
    Node(int a):Num(a),Next(NULL){}

    //从输入创建链表
    //返回头指针
    static Node* createFromInput(){
        Node* head  = NULL;
        Node* tail  = NULL;
        int tmp;

        while(cin >> tmp)
        {
            Node* newNode = new Node(tmp);//利用构造函数

            //连接节点
            if (head == NULL)
            {
                head = newNode;
                tail = newNode;    
                
            }
            else
            {
                tail->Next = newNode;
                tail = newNode;
                
            }
        }
        return head;
    }
};



int main() {
    int k;
    //保护
    if (!(cin >> k)) {return 0;};
    Node* head = Node::createFromInput();
    
    //木棍法
    Node* fast = head;
    Node* slow = head;
    for (int i = 0; i < k; i++)
    {
        //保护
        if (fast == NULL) {
            cout << "Not Found" << endl;
            return 0;
        }
        fast = fast->Next;
        
    }
    
    while (fast!=NULL)
    {
        fast = fast->Next;
        slow = slow->Next;
        
    }

    cout << slow->Num << endl;

    

	return 0;
}
