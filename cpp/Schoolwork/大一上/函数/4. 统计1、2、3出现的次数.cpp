#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

int f(int a, int needFind) {
	int cnt = 0;
	while (a > 0) {
		int tmp = a % 10;
		if (tmp == needFind) {
			cnt++;
		}
		a /= 10;
	}
	return cnt;
}
int main() {
	int num;
	cin >> num;
	int cnt1 = f(num,1);
	int cnt2 = f(num,2);
	int cnt3 = f(num,3);
	cout << cnt1 << ' ' << cnt2 << ' ' << cnt3;

	return 0;
}
