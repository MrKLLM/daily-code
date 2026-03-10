#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif

int fib(int n){
	if(n <= 2){
		return n;//回归
	}
	cout << n <<' ';
	return n * fib(n - 1);//递推
}

/*
递归是 C++ 中非常重要的编程思想，核心是 “函数自己调用自己”，但必须满足两个关键条件（缺一个就会出错）：
终止条件：递归什么时候停止（否则会无限调用，导致栈溢出）；
递归条件：如何把原问题拆解成更小的 “同类子问题”（让函数能重复调用自己）。
用一句话总结：“大事化小，小事化了” —— 把复杂问题拆成和原问题逻辑一致的小问题，直到小问题能直接解决（终止条件）。
*/
int main() {
	
	int b = 5;
	int ret = fib(b);
	cout << ret;
	return 0;
}
