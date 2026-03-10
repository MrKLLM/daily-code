#include<bits/stdc++.h>
using namespace std;

int digit(int num, int k) {
	int digit_cnt = 0;
	int DDDigits[100] ;
	while (num > 0) {
		DDDigits[digit_cnt] = num % 10;
		num /= 10;
		digit_cnt++;
	}
	//如果num位数不足k位则返回0
	if(digit_cnt < k){
		return 0;
	}
	//整数num从右边开始的第k位数字的值
	return DDDigits[k-1];
}
int main() {
	int n, k;
	cin >> n >> k;
	cout << digit(n, k);
	
	return 0;
}

