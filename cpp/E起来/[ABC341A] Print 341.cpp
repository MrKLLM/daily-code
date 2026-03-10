#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int N=0;
	cin >> N;
	for(int i=1;i<=N;i++){
		cout << '1' << '0';
		if(i==N){
			cout << '1';
		}
	}
	return 0;
}
