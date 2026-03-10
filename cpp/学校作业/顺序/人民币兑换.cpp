#include<bits/stdc++.h>
using namespace std;

int main(){
	int a,b,c,d,e;
	int tmp;
	cin>>a;
	b=a/10;tmp=a%10;
	c=tmp/5;tmp=tmp%5;
	d=tmp/2;tmp=tmp%2;
	e=tmp/1;
	cout<<b<<' '<<c<<' '<<d<<' '<<e;
	return 0;
}
