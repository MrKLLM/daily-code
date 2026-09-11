#include<bits/stdc++.h>
using namespace std;

int MaxGYS(int n,int m){
	if(n == m){
		return n;
	}
	if(n < m){
		return MaxGYS(m,n);
	}
	if(m == 0){
		return n;
	}
	return MaxGYS(m,n%m);
}

int main() {
	int n,m;
	cin >> n >> m;
	int res = MaxGYS(n,m);
	cout << res;
	
	return 0;
}
