#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	string S;
	getline(cin, S);
	char maj = 'a';	//初始化
	
	if(S[0]==S[1]){//不少于3个字符
		maj=S[0];
	}else if(S[0]==S[2]){
		maj=S[0];
	}else{
		maj=S[1];
	}
	
	for(long long unsigned int i=0;i<=S.size()-1;i++){
		if(S[i]!=maj){
			cout << i+1 ;
			break;
		}
	}
	return 0;
}
