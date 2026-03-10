#include<bits/stdc++.h>
using namespace std;

int main(){
	char cha;
	cin >> cha;
	if (cha >= 'A' && cha <= 'Z') {
		cout << (char)(cha + 32);
	}
	else if (cha >= 'a' && cha <= 'z') {
		cout << (char)(cha - 32);
	}
	else if (cha >= '0' && cha <= '9') {
		int num = cha - '0';
		cout << num * num;
	}
	else {
		cout << cha;
	}
	
	return 0;
}
