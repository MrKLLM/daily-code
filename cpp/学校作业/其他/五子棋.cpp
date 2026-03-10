#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	for(int i=0;i<14;i++){
		for(int j=0;j<14;j++){
			if(i==5&&(j==5||j==6)){
				cout << "黑";
			}else if(j==5&&(i==4||i==6)){
				cout << "白";
			}else{cout << "十";}
			
		}
		cout << endl;
	}
	return 0;
}
