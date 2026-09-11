#include<bits/stdc++.h>
using namespace std;

int main() {
	string str1,str2;
    getline(cin, str1);
    getline(cin, str2);
    int len1 = str1.size();
    int len2 = str2.size();
    string str3 = str2.substr(0,len2-1) + str1.substr(0,len1-1);
    cout << str3 << endl;
	return 0;
}
