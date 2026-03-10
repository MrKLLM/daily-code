#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif

void f1(int a[],int n){//虚定义数组，长度没有意义，相当于传址，退化为地址
	for(int i=0;i<n;i++){
		a[i] = 2 * a[i];
		cout << a[i] << ' ';
	}
	cout << endl;
}
void f2(int* a,int n){//int* a等价于int a[]
	for(int i=0;i<n;i++){
		cout << a[i] << ' ';
	}
	cout << endl;
}

/*
void f1(int a,int n)	错
……
f1(a , n)	对
f1(a[] , n)	错	
f1(a[8] , n)	错
*/

int main() {
	
	
	return 0;
}
