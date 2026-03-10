#include<bits/stdc++.h>
using namespace std;

int main(){
	float x=0;
	float y=0;
	cin>>x;
	if(x<=-1){
		y=x*2+cos(x);
	}else if(x>=1){
		y=pow(sin(x),2);
	}else{
		y=1/pow(pow(x+1,2),1.0/3.0);
	}
	cout<<y;
	return 0;
}
