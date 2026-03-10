#include <iostream>
using namespace std;

int main() {
	int A, B, C;
	cin >> A >> B >> C;
	
	bool isSleeping;
	// 分两种情况判断A是否在睡觉时间段内
	if (B < C) {
		// 情况1：B到C是睡觉时间（如22点睡，6点醒 → 22~6睡觉）
		isSleeping = (A >= B && A < C);
	} else {
		// 情况2：B到24 + 0到C是睡觉时间（如6点睡，22点醒 → 6~22睡觉）
		isSleeping = (A >= B || A < C);
	}
	
	// 醒着则输出Yes，睡着则输出No
	if (!isSleeping) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
	
	return 0;
}
