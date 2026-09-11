#include<iostream>
#include<string>
#include<cctype>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string s;
	cin >> s;
	int len = s.length();
	
	if(len != 8){
		cout << "No" << endl;
		return 0;
	}
	
	if (DEBUG) {
		cout << s[0] - 1 ;
	}
	
	if (!isupper(s[0])
	    || !isupper(s[7])) {
		cout << "No";
		return 0;
	}
	
	string num_str = s.substr(1,6);
	for(char c:num_str){
		if(!isdigit(c)){
			cout << "No";
			return 0;
		}
	}
	
	int num1 = stoi(num_str);
	if(!(100000<=num1 && num1 <= 999999)){
		cout << "No";
		return 0;
	}
	
	cout << "Yes";
	return 0;
}
