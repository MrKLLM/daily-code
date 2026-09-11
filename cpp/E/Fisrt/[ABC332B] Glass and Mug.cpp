#include<bits/stdc++.h>

using namespace std;

int main(){
	int k = 0;
	int g = 0;
	int m = 0;
	cin >> k >> g >> m;
	
	int glass = 0;
	int mug = 0;
	for(int i=0;i<=(k-1);i++){
		if(glass == g){
			glass = 0;
		}else if(mug == 0){
			mug = m;
		}else{
			int need = g - glass;
			if(mug > g){
				glass = g;
				mug -= need;
			}else{
				glass += mug;
				mug =0;
			}
		}
	}
	
	cout << glass << ' ' << mug;
	return 0;
}
