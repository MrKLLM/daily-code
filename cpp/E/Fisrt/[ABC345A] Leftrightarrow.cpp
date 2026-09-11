#include<bits/stdc++.h>
using namespace std;

int main(){
	string s;
	getline(cin, s);
	
	vector<char> S(s.begin(), s.end());
	
	if(S.front() != '<'){
		cout << "No";
		return 0;
	}
	
	if(S.back() != '>'){
		cout << "No";
		return 0;
	}
	
	for(int i=1;i<=((int)S.size()-2);i++){
		if(S[i] != '='){
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";
	return 0;
}
