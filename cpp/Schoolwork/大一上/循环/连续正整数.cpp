#include<bits/stdc++.h>
using namespace std;

int main() {
	int num = 0;
	bool found = 0;

	cin >> num;
	for (int i = 1 ; i < num ; i++) {
		int sum = 0;
		for (int j = i ; j < num ; j++) {
			sum += j;
			if (sum == num) {
				found = 1;
				for (int k = i ; k <= j ; k++) {
					cout << k << " " ;
				}
				cout << endl;
				break;//找到后退出当前j的循环，继续下一个i
			} else if (sum > num) {
				break;
			}//累加和超过num，无需继续
		}
	}
	if (!found) {
		cout << "none";
	}
	return 0;
}
