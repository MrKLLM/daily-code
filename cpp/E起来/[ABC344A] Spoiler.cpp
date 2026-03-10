#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	string S;
	cin >> S;
	int pos1=S.find('|');
	int pos2=S.find('|',pos1+1);
	string after_cut_S=S.substr(0,pos1)+S.substr(pos2+1);
	cout << after_cut_S;
	return 0;
}
