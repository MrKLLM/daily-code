#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	string s;
	cin >> s;
	
	size_t pos_3 = s.rfind('3');
	s[pos_3] = '4';
	
	cout << s;
	return 0;
}
