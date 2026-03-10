#include<bits/stdc++.h>
using namespace std;

int main(){
	int num;
	cin>>num;
	if(num>=100&&num<=999){
		int hundred=num/100;
		int ten=(num/10)%10;
		int unit=num%10;
		int reservednum=unit*100+ten*10+hundred;
		cout<<reservednum;
	}else{
		cout<<-1;
	}
	return 0;
}
