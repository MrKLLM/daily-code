#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

int main() {
	string str;
	cin >> str;
    // str.pop_back();
	int len = str.size()-1;
	bool is_huiwen = true;
	for (int i = 0; i < len/2; i++)
    {
		if(str[i] != str[len-1-i])
		{
			is_huiwen = false;
			break;
		}
    }
    if (is_huiwen)
	{
		cout << len << endl;
	}
	else
	{
		cout << "no" << endl;
	}
	
	return 0;}
