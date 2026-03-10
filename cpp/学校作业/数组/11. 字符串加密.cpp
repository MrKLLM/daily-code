#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	string s;
	cin >> s;
	for(string::size_type i=0;i<=s.length()-1;i++){
		
		int dist = 0;
		if(('a'<=s[i])&&(s[i]<='z')){
			
			dist = 'z'-s[i];
			
			if(dist>=4){
				cout << (char)(s[i]+4);
			}else{
				cout << (char)(('a'-1)+(s[i]-'z'+4));
				
			}
		} else if(('A'<=s[i])&&(s[i]<='Z')){ 
			
			dist = 'Z'-s[i];
			
			if(dist>=4){
				cout << (char)(s[i]+4);
			}else{
				cout << (char)(('A'-1)+(s[i]-'Z'+4));
				
			}
		} 
	}
	
	return 0;
}
