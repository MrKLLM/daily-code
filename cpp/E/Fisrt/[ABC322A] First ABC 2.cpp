#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	int n;
	cin >> n;
	string s;
	cin >> s;
	
	size_t pos = s.find("ABC");
	
	if(pos != string::npos){
		cout << pos+1;
	}
	else{
		cout << -1;
	}
	return 0;
}
