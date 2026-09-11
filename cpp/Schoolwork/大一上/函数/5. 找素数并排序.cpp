#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

int* findPrime(int nums[], int n, int& primeCnt) {
	int* primes = new int[100];
	/*
	如果声明int primes[100];
	最后返回了一个局部数组primes的地址，
	而局部变量在函数执行结束后会被销毁，
	导致返回的指针变成 “野指针”，
	访问它会出现未定义行为（比如输出乱码、崩溃或无输出）
	*/
	primeCnt = 0;
	for (int i = 0; i < n; i++) {
		int a = nums[i];
		//先考虑2的情况
		if (a == 2) {
			primes[primeCnt++] = a;
			continue;
		}
		
		if ((a <= 1 || a % 2 == 0 )) {
			continue;
		} else {
			int isPrime = true;
			for (int j = 3; j * j <= a; j += 2) {
				if (a % j == 0) {
					isPrime = false;
					break;
				}
			}
			if (isPrime) {
				primes[primeCnt++] = a;
			}
		}
	}
	return primes;
}

void sortArr(int* arr, int len) {
	for (int i = 0; i < len - 1; i++) {
		
		for (int j = 0; j < len - 1 - i; j++) {//
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
int main() {
	int n;
	cin >> n;
	int nums[100];
	for (int i = 0; i < n; i++) {
		int a = 0;
		cin >> a;
		nums[i] = a;
	}
	int primeCnt = 0;//质数个数
	int* primess = findPrime(nums, n, primeCnt);
//	sort(primess,primess+primeCnt);
	sortArr(primess,primeCnt);
	for (int i = 0; i < primeCnt; i++) {
		cout << primess[i];
		if (i != primeCnt - 1) {
			cout << ' ';
		}
	}
	return 0;
}
