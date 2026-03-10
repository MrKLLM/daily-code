#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif
#ifndef MAX
	#define MAX (10)
#endif

int main() {
	char cha1[MAX] = "China";
	char cha2[MAX] = "hi";
	
	int len1 = strlen(cha1);
	int len2 = strlen(cha2);
	
	for(int offset=0;offset < len1;offset++){
		
		bool dif = false;
		for(int i=0;i<=len2;i++){
			
			if(cha2[i] != cha1[offset + i]){
				dif = true;
				break;
			}
		}
	}
	return 0;
}
