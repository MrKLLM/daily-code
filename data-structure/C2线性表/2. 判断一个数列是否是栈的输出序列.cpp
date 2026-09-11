#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif

int main() {
	int n = 0;
	cin >> n;
	
	int push_arr[n+1];
	int pop_arr[n+1];
	
	for(int i=0;i<n;i++){
		int tmp = 0;
		cin >> tmp;
		push_arr[i] = tmp;
	}
	
	for(int i=0;i<n;i++){
		int tmp = 0;
		cin >> tmp;
		pop_arr[i] = tmp;
	}
	
	int* stack = new int[n+1];
	int top = -1;//堆顶为空
	int p1 = 0;//输入序列指针
	int p2 = 0;//输出序列指针
	
	while(p2 < n){
		if(top == -1 || stack[top] != pop_arr[p2]){
			if(p1>n){
				break;
			}
			stack[++top] = push_arr[p1++];
			
		}else{
			top --;
			p2 ++;
		}
	}
	
	if(p2 == n){
		cout << p2;
	}else{
		cout << 0;
	}
	return 0;
}
