#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
void ten2other(int a, const int b) {
	//归，触底
	if (a == 0) {
		return;
	}
	//递
	ten2other(a / b, b);
	//压栈，待执行
	cout << a % b;
}

int main() {
	int n = 0;
	int ten = 0;

	cin >> n >> ten ;
	ten2other(ten, n);

	return 0;
}
