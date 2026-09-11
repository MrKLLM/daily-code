#include<bits/stdc++.h>
using namespace std;


struct number {
	int num;
	number* next;
};

number* creatNode(int new_num) {
	number* newNode = new number;
	newNode->num = new_num;
	newNode->next = NULL;
	return newNode;
}

//查找并删除目标节点的函数
//number*& head前有&是因为函数中要修改head,所以要引用它
void deleteTarget(number*& head,int target){
	//case1: 链表为空，回家吧孩子
	if(head == NULL){
		return;
	}
	
	number* toDelete = NULL;//土地利特搜查官，不死的巨噬细胞（化身为要被删除的节点）
	number* current = head;//卡伦搜查官，用来开路（遍历）的节点
	
	//case2: 头节点就是要删掉的目标
	if(head->num == target){
		
		toDelete = head;//土地利特搜查官来家里了
		head = head->next;//逃跑到下一个房子，代价是丢掉原来房子的东西
		delete toDelete;//土地利特搜查官自爆（但不死）
	}
	
	//case3: 删除目标位于中间或末尾，得遍历节点（卡伦搜查官一间间房子找）
	while(current->next != NULL){
		//***好好看好好学，删节点精髓***
		if(current->next->num == target){//（找到目标节点的前一个节点）卡伦在上一座房子远远看见了嫌疑犯
			toDelete = current->next;//土地利特搜查官出马，至于为什么都是从目标房子的上一个房子出发，是为了不打草惊蛇
			current->next = current->next->next; //[跳过目标节点（删除)]嫌疑犯逃跑，重新做人（偶不，是重新做节点）
			delete toDelete;//但没事儿，引爆赃物就好
			return;//下班回家
		}
		//根据屋子里留下的纸条————写着下一座房子的地址，移动至下一节点
		current = current->next;
	}
	
	//case4: 在链表中（所有房子）没找到嫌疑犯，那就……回家，但是至此，函数已经结束了，不用return也会自动回家的
}

//打印链表
void printList(number* head){
	number* current = head;
	while(current != NULL){
		cout << current->num;//要什么就直接拿吧，累了
		if (current->next != NULL) {
			cout << " ";  // 最后一个节点后不输出空格
		}
		current = current->next;// 移动到下一个节点
		//***错误2：原来没有节点移动代码，卡伦搜查官得着一个房子薅，不去下一栋房子***
	}
	cout << endl;
}

//释放内存
void freeList(number*& head){//你是要修改head，要用&引用它喔
	number* tmp;//重生并继续救人
	while(head != NULL){//便利店（bushi,是遍历
		tmp = head;//tmp:"快……快跑……我来顶替你，这里……快爆炸了
		head = head->next;//head:"好——好的，我不会而忘了你的"[含泪转身离开]
		delete tmp;//Bomb！！！(拟声词)
	}
}
int main() {

	//构建单链节点
	number* head = NULL;
	while (1) {
		int tmp = 0;
		cin >> tmp;
		if (tmp == -1) {
			break;
		}

		number* newCode = creatNode(tmp);
		//***下面两句，好好看好好学，头插法精髓***
		newCode->next = head;//head只是个指针，是一个地址的记事本
		head = newCode;//刷新记事本上记着的地址
		//***错误1：原： newCode= head;导致创建的节点并没有赋给头节点***
		
	}
	//其实仔细想想，head(有时还有tail)是整条链表的接口（切口）

	int target;
	cin >> target;
	
	deleteTarget(head, target);
	
	printList(head);
	
	//释放内存（好习惯）
	freeList(head);
	
	return 0;
}
