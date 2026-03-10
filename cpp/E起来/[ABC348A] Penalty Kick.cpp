#include<bits/stdc++.h>
using namespace std;

int main(){
	int N=0;
	cin >> N;
	for(int i=1;i<=N;i++){
		if(i<=2){
			cout << 'o';
		}
		else{
			if(i%3==0){
				cout << 'x';
			}else{
				cout << 'o';
			}
		}
	}
	return 0;
}
