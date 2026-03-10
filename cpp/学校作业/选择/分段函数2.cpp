#include<bits/stdc++.h>
using namespace std;

int main(){
	float x=0;
	float y=0;
	cin>>x;
	if(x<=-1){
		y=3*sqrt(abs(x)+2)+1;
	}else if(x>10){
		y=sqrt((x+1)/(2*pow(x,2)));//TODO
	}else{
		y=pow(x,5)+1;
	}
	cout <<y;
	return  0;
}
