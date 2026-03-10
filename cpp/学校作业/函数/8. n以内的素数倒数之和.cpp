#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

int* findPrime(int n, int& primeCnt) {
	int* primes = new int[n + 5];
	/*
	如果int primes[100];
	最后返回了一个局部数组primes的地址，
	而局部变量在函数执行结束后会被销毁，
	导致返回的指针变成 “野指针”，
	访问它会出现未定义行为（比如输出乱码、崩溃或无输出）
	*/
	primeCnt = 0;

	for (int i = 2; i <= n; i++) {
		if (i == 2) {
			primes[primeCnt++] = i;
			continue;
		}
		if ((i <= 1 || i % 2 == 0 )) {
			continue;
		} else {
			int isPrime = true;
			for (int j = 3; j * j <= i; j += 2) {
				if (i % j == 0) {
					isPrime = false;
					break;
				}
			}
			if (isPrime) {
				primes[primeCnt++] = i;
			}
		}
	}
	return primes;
}

void sortArr(int* arr, int len) {
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

double calSumOfRecpPrime(int primeArr[], const int primeCnt, int index = 0) {
	// 终止条件：索引超出质数个数
	if (index >= primeCnt) {
		return 0.0;
	}
	double curr = 1.0 / primeArr[index];
	// 递：递归调用下一个索引；归：累加当前倒数
	return curr + calSumOfRecpPrime(primeArr, primeCnt, index + 1);
	/*
	这里index是值传递，index++是 “先传值、再自增”
	但自增只在当前函数的index变量生效，
	下一次递归的index参数还是原来的数值（比如第一次index=0，传的还是0）。
	这会导致无限递归：index永远不会增长到primeCnt，调用栈越堆越深，最终触发栈溢出，报 SIGSEGV。
	*/
}
int main() {
	int n;
	cin >> n;


	int primeCnt = 0;//质数个数
	int* primess = findPrime( n, primeCnt);
	sort(primess, primess + primeCnt); // 排序质数数组
//	sortArr(primess,primeCnt);
	double sum = calSumOfRecpPrime(primess, primeCnt); // 计算倒数和
	cout << sum;
	delete[] primess; // 释放堆内存，避免泄漏
	return 0;
}
/*
你的理解完全精准！这正是递归的核心 ——「先递后归」：先一层层向下调用（压栈）直到触底（触发终止条件），再从最底层开始反向逐层返回、计算（弹栈），最终汇总出所有层的结果。
我们用一个具体例子（质数数组[2,3,5]，primeCnt=3），一步步拆解栈的「压入」和「弹出」过程，你就能直观看到return 0.0后发生了什么：
先明确核心概念
压栈（递）：每调用一次calSumOfRecpPrime，函数会暂停执行（保留当前变量状态），把自己 “压” 到内存的「调用栈」里，然后执行新的递归调用；
弹栈（归）：当触发终止条件return 0.0（触底），最底层的函数执行完毕并返回值，栈开始 “弹出”，暂停的函数会从暂停处继续执行剩余逻辑，直到所有层都弹完。
示例拆解：质数数组 [2,3,5]，primeCnt=3
静态变量i初始为 0，我们一步步看栈的变化：
第一步：递（压栈）—— 一层层调用，直到触底
调用次数	执行逻辑														栈状态（从上到下是栈顶→栈底）								i 的值
第 1 次		i=0 < 3，计算currentReciprocal=1.0/2，i++变为 1，递归调用自身	[第 1 次函数（暂停：待执行return 0.5 + 第2次调用结果）]		1
第 2 次		i=1 < 3，计算currentReciprocal=1.0/3，i++变为 2，递归调用自身	[第 2 次函数（暂停：待执行return 0.3333... + 第3次调用结果）
																			第 1 次函数（暂停）]										2
第 3 次		i=2 < 3，计算currentReciprocal=1.0/5，i++变为 3，递归调用自身	[第 3 次函数（暂停：待执行return 0.2 + 第4次调用结果）
																			第 2 次函数（暂停）
																			第 1 次函数（暂停）]										3
第 4 次		i=3 >= 3（触底），执行i=0重置，return 0.0						[第 4 次函数（执行中：触发终止条件）
																			第 3 次函数（暂停）
																			第 2 次函数（暂停）
																			第 1 次函数（暂停）]										0（重置后）
第二步：归（弹栈）—— 从底层开始，逐层计算返回
触发return 0.0后，栈开始 “反向弹出”，每一层暂停的函数会继续执行剩余逻辑：
第 4 次函数弹栈：返回0.0给调用它的「第 3 次函数」，第 4 次函数执行完毕，从栈中消失；
第 3 次函数继续执行：拿到第 4 次的返回值0.0，计算0.2 + 0.0 = 0.2，然后return 0.2给「第 2 次函数」，第 3 次函数弹栈；
第 2 次函数继续执行：拿到第 3 次的返回值0.2，计算0.3333... + 0.2 = 0.5333...，然后return 0.5333...给「第 1 次函数」，第 2 次函数弹栈；
第 1 次函数继续执行：拿到第 2 次的返回值0.5333...，计算0.5 + 0.5333... = 1.0333...，然后return 1.0333...给main函数，第 1 次函数弹栈；
最终，main函数拿到的结果就是1/2 + 1/3 + 1/5 = 1.0333333333333332。
关键补充：栈里 “剩余函数部分” 是什么？
每一层函数暂停时，“没执行完的部分” 就是：return currentReciprocal + 下一次递归调用的结果
只有等下一次递归调用返回具体值（比如底层的0.0，或者上层的0.2），这一行才能算出结果并返回。
简单说：
「递」：把所有 “待计算的层” 压到栈里，直到触底；
「归」：从底往上，用return 0.0这个 “基础值”，逐层算出每一层的结果，最终汇总。
*/
