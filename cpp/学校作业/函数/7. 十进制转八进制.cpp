#include<iostream>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

/*
递归调用并不是 “无限执行下去”，而是会触底（触发基线条件）后回溯，回溯时就会执行输出语句。
核心是要理解：递归函数的调用是 “栈式” 的，先调用的函数会暂停，等子调用全部完成后，才会继续执行调用后的代码。
先看核心逻辑：递归的 “递” 和 “归” 是分两步的
*/
void ten_to_others(int m, int n) {
	if (m == 0) {
		return;
	}
//	递归函数的执行分为两个阶段：
//	递（向下调用）：不断调用 ten_to_others(n/8)，直到触发基线条件（n=0），这一阶段只做 “调用”，不做 “输出”；
	ten_to_others(m / n, n);
//	归（向上回溯）：从最内层的递归调用返回后，逐层执行暂停的代码（也就是 cout << n%8），这一阶段才是输出的核心。
	cout << m % 8;
}
int main() {
	int a;
	int b = 8;
	cin >> a;
	ten_to_others(a, b);

	return 0;
}
/*
1	第一层（125）	ten_to_others(125/8=15)	先执行递归调用，cout << 125%8 被暂停，等待 ten_to_others(15) 执行完毕
2	第二层（15）	ten_to_others(15/8=1)	同理，cout << 15%8 暂停，等待 ten_to_others(1) 执行完毕
3	第三层（1）	ten_to_others(1/8=0)	同理，cout << 1%8 暂停，等待 ten_to_others(0) 执行完毕
4	第四层（0）	if(n==0) return;	触发基线条件，直接返回，没有更多递归调用，也没有输出
5	回溯到第三层（1）	执行暂停的 cout << 1%8	输出 1，第三层函数执行完毕，返回第二层
6	回溯到第二层（15）	执行暂停的 cout << 15%8	输出 7，第二层函数执行完毕，返回第一层
7	回溯到第一层（125）	执行暂停的 cout << 125%8	输出 5，第一层函数执行完毕，整个递归结束
*/
