#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main() {
	int T_cnt = 0;
	int A_cnt = 0;
	int n;
	cin >> n >> A_cnt >> T_cnt;
	int remaining = n-(A_cnt+T_cnt);
	
	int smaller = T_cnt>A_cnt?A_cnt:T_cnt;
	int bigger = T_cnt>A_cnt?T_cnt:A_cnt;
	if(bigger > smaller+remaining){
		cout << "Yes";
	}else{
		cout << "No";
	}
	return 0;
}
