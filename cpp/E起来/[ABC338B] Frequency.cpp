#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	string S;
	getline(cin,S);
	map <char , int> frq;
	for(char cha : S){
		frq[cha]++;
	}
	
	int max_frq = 0;
	for(char i='a';i<='z';i++){
		if(max_frq <= frq[i]){
			max_frq = frq[i];
		}
	}//比较
	
	for(char i='a';i<='z';i++){
		if(max_frq == frq[i]){
			cout << i;
			break;
		}
	}//筛选
	return 0;
}
