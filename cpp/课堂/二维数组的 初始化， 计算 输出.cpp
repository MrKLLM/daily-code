#include <iostream>
#include <cmath>
using namespace std;
#ifndef MAX
	#define MAX  (3)
#endif
int main() {
	int a[MAX][MAX] {0};	// 二维数组的定义、就地初始化
	int b[MAX][MAX] {0};
	int c[MAX][MAX] {0};
	// 常规二维矩阵的输入
	// 先输入A矩阵
	for (int i = 0; i < MAX; i++) {		//i表示行
		for (int j = 0; j < MAX; j++) {	// j表示列
			cin >> a[i][j];
		}

	}

	// 再输入B矩阵
	for (int i = 0; i < MAX; i++) {		//i表示行
		for (int j = 0; j < MAX; j++) {	// j表示列
			cin >> b[i][j];
		}
	}

	// 在计算部分之前可以打断点，检查输入是否正确

	// 计算部分
	for (int i = 0; i < MAX; i++) {		//i表示行
		for (int j = 0; j < MAX; j++) {	// j表示列
			c[i][j] = a[i][j] + b[i][j];
		}
	}

	// 常规二维数组的输出
	for (int i = 0; i < MAX; i++) {		//i表示行
		for (int j = 0; j < MAX; j++) {	// j表示列
			cout << c[i][j] << '\t';
		}
		cout << endl;		// 换行

	}

	return 0;
}
