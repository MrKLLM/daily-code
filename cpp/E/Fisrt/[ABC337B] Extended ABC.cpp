#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	string s;
	cin >> s;
	
	size_t posA = s.find_first_not_of('A');
	if(posA == string::npos){
		cout << "Yes";
		return 0;
	}
	
	size_t posB = s.find_first_not_of('B',posA);
	if(posB == string::npos){
		cout << "Yes";
		return 0;
	}
	
	size_t posC = s.find_first_not_of('C',posB);
	if(posC == string::npos){
		cout << "Yes";
		return 0;
	}else{
		cout << "No";
		return 0;
	}
	
	return 0;
}
