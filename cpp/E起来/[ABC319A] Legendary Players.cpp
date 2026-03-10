#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	map <string ,int> user_score = {
		{"tourist", 3858},
		{"ksun48", 3679},
		{"Benq", 3658},
		{"Um_nik", 3648},
		{"apiad", 3638},
		{"Stonefeang", 3630},
		{"ecnerwala", 3613},
		{"mnbvmar", 3555},
		{"newbiedmy", 3516},
		{"semiexp", 3481},
	};
	
	string username;
	cin >> username;
	cout << user_score[username];
	return 0;
}
