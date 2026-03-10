#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	string s;
	cin >> n >> s;

	bool foundA = false;
	bool foundB = false;
	bool foundC = false;
	for (int i = 0; i < n; i++) {

		if (s[i] == 'A') {
			foundA = true;
		} else if (s[i] == 'B') {
			foundB = true;
		} else if (s[i] == 'C') {
			foundC = true;
		}

		if (foundA && foundB && foundC) {
			cout << i+1;
			return 0;
		}
	}

	return 0;
}
