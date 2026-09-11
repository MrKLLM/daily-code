#include <iostream>
#include <vector>
#include <algorithm> // 包含 reverse

using namespace std;

void myReverse(int arr[], int start, int end) {
	while (start < end) {
		int temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}

// 调用逻辑：
// myReverse(array_R, 0, shift - 1);
// myReverse(array_R, shift, n - 1);
// myReverse(array_R, 0, n - 1);

int main() {
	int n, shift;
	if (!(cin >> shift >> n)) return 0;
	
	shift %= n; // 处理位移量大于数组长度的情况
	
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	// 1. 翻转 [0, shift-1]
	reverse(nums.begin(), nums.begin() + shift);
	// 2. 翻转 [shift, n-1]
	reverse(nums.begin() + shift, nums.end());
	// 3. 翻转整个数组 [0, n-1]
	reverse(nums.begin(), nums.end());
	
	// 输出结果
	for (int i = 0; i < n; i++) {
		cout << nums[i] << (i == n - 1 ? "" : " ");
	}
	
	return 0;
}
