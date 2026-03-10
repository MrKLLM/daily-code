#include<bits/stdc++.h>
using namespace std;

//传地址
void swap1(int *x,int *y){
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

//传值
void swap2(int x,int y){
	int tmp = x;
	x = y;
	y = tmp;
}

//传递引用，长得像变量，实际是地址（外号）
void swap3(int &x,int &y){
	int tmp = x;
	x = y;
	y = tmp;
}
#ifndef DEBUG
#define DEBUG (0)
#endif
#ifndef MAX
#define MAX ()
#endif

int main() {
	int a = 1;
	int b = 2;
	swap2(a ,b);
	cout << a <<' ' << b;
	return 0;
}
