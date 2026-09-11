#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

int main() {
	int n;
	cin >> n;
	int L[20];
	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		L[i] = tmp;
	}

	int p1 = 0;
	for(int i=1;i<n;i++){
		if(L[i] != L[p1]){
			L[++p1] = L[i];
		}
	}
	
	n = p1 + 1;//有效长度
	for(int i=0;i<n;i++){
		cout << L[i] << ' ';
	}
	return 0;
}
