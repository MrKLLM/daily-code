#include<bits/stdc++.h>
using namespace std;

int main(){
	string S;
	getline(cin,S);
	vector <char> str;
	str.assign(S.begin(),S.end());
	
	bool only_first_capitalized = true;
	
	if(!(S[0] >= 'A' && S[0] <= 'Z')){
		only_first_capitalized = false;
	}
	for(int i=1;i<(int)str.size();i++){
		if(!(S[i] >= 'a' && S[i] <= 'z')){
			only_first_capitalized = false;
			break;
		}
	}
	
	cout << (only_first_capitalized ? "Yes" : "No");
	return 0;
}
