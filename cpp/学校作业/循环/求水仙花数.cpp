#include<bits/stdc++.h>
using namespace std;

int main(){
	int num=0;
	cin>>num;
	for(int i=100;i<=num;i++){
		int hundred=i/100;
		int ten=(i/10)%10;
		int unit=i%10;
		int tmp = hundred * hundred * hundred + ten * ten * ten + unit * unit * unit;
		if(tmp==i){
			cout<<i<<' ';
		}
	}
	return 0;
}
