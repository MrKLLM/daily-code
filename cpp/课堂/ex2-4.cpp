#include <iostream>
using namespace std;
#ifndef MAX
	#define MAX  (10)
#endif
int main() {
	int a;
	cin >> a;
	int b;
	cin >> b;

	int yue = 2;
	int bei = a;

	//公约数 2~a 2~b之间
	for (int i = 2; i <= a / 2; i++) {
		if ((a % i ==  0)
		    && ( b % i == 0) ) {
			yue = i;
		}
	}

	// 最小gongbei数 a~a*b   b~a*b
	for (int i = a; i <= a * b; i++) {
		if ((i % a ==  0)
		    && ( i % b == 0) ) {
			bei = i;
			break;
		}
	}

	cout << yue << ' ' << bei;
}
