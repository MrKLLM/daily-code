#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG ()
#endif
#ifndef MAX
	#define MAX ()
#endif
int main() {
	int n;
	cin >> n;

	int seq_sum = 2;
	int* Fibonacci = new int [n + 5];
	if (1 == n) {
		cout << 1;
	} else if (2 == n) {
		cout << 2;
	} else {
		Fibonacci[0] = 1;
		Fibonacci[1] = 1;
		for (int i = 2; i <= (n - 1); i++) {
			Fibonacci[i] = Fibonacci[i - 1] + Fibonacci[i - 2];
			seq_sum += Fibonacci[i];
		}
	}

	cout << seq_sum;
}
