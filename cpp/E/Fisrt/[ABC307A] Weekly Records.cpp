#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX (7)
#endif
int main() {
	int n;
	cin >> n;
	int steps = 0;
	
	for(int i=0;i<n;i++){
		steps = 0;
		for(int j=0;j<MAX;j++){
			int a = 0;
			cin >> a;
			steps+= a;
		}
		cout << steps <<' ';
	}
	
	return 0;
}
