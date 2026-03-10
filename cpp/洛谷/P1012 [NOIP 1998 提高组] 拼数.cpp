#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

typedef string type;

bool cmp(type a, type b) {
	return ((a + b) > (b + a));
}
int main() {
	int n;
	cin >> n;
	string strs[20] {};
	for (int i = 0; i < n; i++) {
		cin >> strs[i];
	}

	sort(strs, strs + n, cmp);
	
	string result = "";
	
	for(int i=0;i<n;i++){
		result += strs[i];
	}
	cout << result;
	return 0;
}
