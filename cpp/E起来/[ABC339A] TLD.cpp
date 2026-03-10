#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	string S;
	getline(cin,S);
	int pos = S.rfind('.');
	string suffix = S.substr(pos+1);
	cout << suffix;
	return 0;
}
