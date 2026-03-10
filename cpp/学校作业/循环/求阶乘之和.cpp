#include<bits/stdc++.h>
using namespace std;

int main(){
	double s=0,n=0;
	double tmp=1;
	cin>>n;
	for(double i=1;i<=n;i++){
		tmp*=i;
		s+=tmp;
	}
	cout<<s;
	return 0;
}
