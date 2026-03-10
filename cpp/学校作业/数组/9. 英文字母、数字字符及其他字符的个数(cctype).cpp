#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	string s ;
	cin >> s;
	
	int alpha_count = 0;
	int digital_count = 0;
	int others_count = 0;
	
//	for(auto i=0u;i<=(s.length()-1);i++){
//		int c = s[i];
//		
//		if((( c >= 'a' )&&( c <= 'z' ))
//		   ||((c>='A') && (c<='Z'))){
//			alpha_count++;
//		}else if( (c >= '0' )&&( c <= '9' )){
//			digital_count++;
//		}else{
//			others_count++;
//		}
//	}
	for(string::size_type i=0;i<=(s.length()-1);i++){
//		int c = s[i];
		
//		if((( c >= 'a' )&&( c <= 'z' ))
//		   ||((c>='A') && (c<='Z'))){
//			alpha_count++;
//		}else if( (c >= '0' )&&( c <= '9' )){
//			digital_count++;
//		}else{
//			others_count++;
//		}
		if (isalpha(s[i])) {
			alpha_count++;
		} else if (isdigit(s[i])) {
			digital_count++;
		} else {
			others_count++;
		}
	}
	
	cout << alpha_count << ' ' << digital_count << ' ' << others_count;
	return 0;
}
