#include <iostream>
using namespace std;
#ifndef MAX
	#define MAX  (10)
#endif
int main() {
	int n = 15;


	for (int k = 1; k < n; k++) {
		int sum = 0;
		for (int i = k; i < n; i++) {
			sum += i;
			if (n == sum) {
				cout << n << '=';
				for (int j = k; j <= i; j++) {
					cout << j << '+';
				}
				cout << endl;
			}
			if (sum > n) {
				break;
			}
			//TODO
		}
	}
}
