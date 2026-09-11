#include<bits/stdc++.h>
using namespace std;

int main(){
	float q=0;
	float sn=0;
	cin >> q;
	for(int n=1;sn<q;n++){
		float tmp=1.0*(n+1)/n;
		sn=sn+tmp;
	}
	cout<<sn;
	return 0;
}
