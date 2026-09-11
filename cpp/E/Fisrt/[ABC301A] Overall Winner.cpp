#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	int T_cnt = 0;
	int A_cnt = 0;
	for(int i=0;i<n;i++){
		if(s[i] == 'T'){
			T_cnt++;
		}else{
			A_cnt++;
		}
	}
	
	if(T_cnt > A_cnt){
		cout << 'T';
	}else if(A_cnt > T_cnt ){
		cout << 'A';
	}else{
		if(s[n-1] == 'A'){
			cout << 'T';
		}else{
			cout << 'A';
		}
	}
	return 0;
}
