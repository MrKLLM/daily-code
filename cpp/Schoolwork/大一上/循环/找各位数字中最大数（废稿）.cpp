#include<bits/stdc++.h>
using namespace std;

int main(){
	int num =0;
	cin >>num;
	
	int val[num];
	int tmp1 =num;
	int tmp2=0;
	int i=1;
	int n=1;
	
	while(tmp1 >=1){
		val[i] =tmp1%10;
		tmp1/=10;
		i++;
	}
	
	for( ;i>0 ;i--){
		if(tmp2 <=val[n]){
			tmp2=val[n];}
		n++;
	}
	cout <<tmp2;
	return 0;
}
