#include<bits/stdc++.h>
using namespace std;

int main(){
	int num=0;
	cin>>num;
	if (num%3==0&&num%7!=0) {
		cout<<1;
	} else if (num%3!=0&&num%7==0) {
		cout<<2;
	} else if (num%3==0&&num%7==0) {
		cout<<3;
	} else {
		cout<<4;
	}
	return 0;
}
