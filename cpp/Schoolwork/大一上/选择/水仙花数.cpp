#include<bits/stdc++.h>
using namespace std;

int main(){
	int num=0;
	cin>>num;
	if(num>=100&&num<=999){
		int hundred=num/100;
		int ten=(num/10)%10;
		int unit=num%10;
		int tmp = hundred * hundred * hundred + ten * ten * ten + unit * unit * unit;
		if (tmp == num) {
			cout << "YES";
		} else {
			cout << "NO";
		}
	}else{
		cout<<"NO";
	}
	return 0;
}
