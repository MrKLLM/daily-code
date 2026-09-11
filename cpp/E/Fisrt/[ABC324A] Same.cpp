#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
int main() {
	int n;
	cin >> n;
	int* nums = new int[n];

	for (int i = 0; i < n; i++) {

		cin >> nums[i];
	}

	int maj = 0;
	maj = nums[0];
	bool same = false;
	for (int i = 1; i < n; i++) {
		same = true;
		if (nums[i] != maj) {
			cout << "No";
			same = false;
			break;
		}

	}

	if (same) {
		cout << "Yes";
	}
	delete[]nums;
}
