#include<bits/stdc++.h>
using namespace std;

int main(){
	int n = 0;
	cin >> n;
	cin.ignore();
	string s;
	getline(cin,s);
	
	
	if (s.find("ab") != string::npos 
		|| s.find("ba") != string::npos) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
	return 0;
}
