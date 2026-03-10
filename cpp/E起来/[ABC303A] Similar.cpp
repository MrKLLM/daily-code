#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
int main() {

	int n;
	cin >> n;
	string s1,s2;
	cin >> s1 >> s2;
	
	int simiar_cnt = 0;
	for(int i=0;i<n;i++){
		
		if(s1[i] == s2[i]){
			simiar_cnt++;
		}else if((s1[i] == '1' || s1[i] == 'l') 
				 && (s1[i] == '1' || s1[i] == 'l')){
			simiar_cnt++;
		}else if((s1[i] == '0' || s1[i] == 'o') 
				 && (s1[i] == '0' || s1[i] == 'o')){
			simiar_cnt++;
		}else{
			cout << "No";
			return 0;
		}
		
		if(simiar_cnt == n){
			cout << "Yes";
		}
	}
	
	return 0;
}
