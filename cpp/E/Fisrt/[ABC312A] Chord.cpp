#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
int main() {
	string s;
	cin >> s;
	vector<string> fng_str = {"ACE", "BDF", "CEG", "DFA", "EGB", "FAC", "GBD"};
	if (find(fng_str.begin(), fng_str.end(), s) != fng_str.end()) {
		cout << "Yes" ;
	} else {
		cout << "No" ;
	}

	return 0;
}
