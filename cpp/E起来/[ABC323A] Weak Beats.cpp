#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
int main() {
	string s;
	cin >> s;

	bool weak_beats = false;
	for (int i = 1; i < 16; i += 2) {
		if (s[i] != '0') {
			cout << "No";
			weak_beats = false;
			break;
		}
		weak_beats = true;
	}

	if(weak_beats){
		cout << "Yes";
	}
	return 0;
}
