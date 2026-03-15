#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 0;
	int shift = 0;
	cin >> shift >> n;
	shift%=n;//处理边界，避免是shift >= n
	
	int* array_R = new int[n + 1];
	for (int i = 0; i < n; i++) {
		int num = 0;
		cin >> num;
		array_R[i] = num;
	}

	for (int i = shift; i < n; i++) {
		cout << array_R[i] << " ";
	}

	for (int i = 0; i < shift; i++) {
		cout << array_R[i] << " ";
	}
	
	return 0;
}
