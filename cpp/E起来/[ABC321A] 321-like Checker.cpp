#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
int main() {

	string s;
	cin >> s;
	int nums[6];
	size_t length = 0;
	for (string::size_type i = 0; i < s.length(); i++) {

		nums[i] = s[i] - '0';
		length++;
	}
		
	int tmp = nums[0];
	bool is_321 = false;
	for (size_t i = 1; i < length; i++) {
		
		if (tmp > nums[i]) {

			is_321 = true;
			tmp = nums[i];
			if(i == length-1){
				break;
			}
		} else {

			is_321 = false;
			cout << "No";
			break;
		}
	}

	if (1 == length) {
		is_321 = true;
	}


	if (is_321) {
		cout << "Yes";
	}
	return 0;
}
