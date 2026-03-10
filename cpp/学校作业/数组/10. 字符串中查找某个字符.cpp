#include<bits/stdc++.h>
using namespace std;

int main(){
	
	string s;
	getline(cin,s);
	char find = 0;
	cin >> find;
	bool haved_fnd = false;
	
	for(string::size_type i=0 ;i<=(s.length()-1) ;i++){
		if (s[i] == find) {
			cout << i << endl;
			haved_fnd = true;
			break;
		}
	}if(!haved_fnd){
		cout << "no" << endl;
	}
	
	return 0;
}
