#include<bits/stdc++.h>
 using namespace std;
#ifndef MAX
	#define MAX (10)
#endif
int main() {
	int nums[8] = {0};
	
	for(int i=0;i<=7;i++){
		int a = 0;
		cin >> a;
		nums[i] = a;
	}

	for (int i = 0; i < 6; i++) { //检查单调性

		if (nums[i] <= nums[i + 1]) {
			
			continue;
		}else {
			cout << "No";
			return 0;
		}
	}
	
	for(int i=0;i<=7;i++){//?in 100~675
		if(100 <= nums[i] 
		   && nums[i] <= 675){
			
			continue;
		}else{
			cout << "No";
			return 0;
		}
	}
	
	for(int i=0;i<=7;i++){//？整除25
		if(nums[i]%25 == 0){
			continue;
		}else{
			cout << "No";
			return 0;
		}
	}
	
	cout << "Yes";
	return 0;
}
