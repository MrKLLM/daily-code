#include<bits/stdc++.h>
using namespace std;

int main(){
	int year=0,month=0;
	cin>>year>>month;
	switch (month) {
	case 4:
		cout<<30;
		break;
	case 6:
		cout<<30;
		break;
	case 9:
		cout<<30;
		break;
	case 11:
		cout<<30;
		break;
	case 2:
		if((year%4==0 && year%100!=0)||(year%400==0)){
		cout<<29;
	}else{
		cout<<28;
	}
		break;
	
	default:
		cout<<31;
		break;
	}
	return 0;
}
