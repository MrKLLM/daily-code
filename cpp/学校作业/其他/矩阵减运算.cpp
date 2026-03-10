#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX (3)
#endif
int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int a[MAX][MAX] {0}; // 二维数组的定义、就地初始化
	int b[MAX][MAX] {0};
	int c[MAX][MAX] {0};
	int d[MAX][MAX] {0};
	int e[MAX][MAX] {0};
	//输入A矩阵
	for (int i = 0; i < MAX; i++) { //i表示行
		for (int j = 0; j < MAX; j++) { // j表示列
			cin >> a[i][j];
		}
	}
	//输入B矩阵
	for (int i = 0; i < MAX; i++) { //i表示行
		for (int j = 0; j < MAX; j++) { // j表示列
			cin >> b[i][j];
		}
	}
	//算差
	for (int i = 0; i < MAX; i++) { //i表示行
		for (int j = 0; j < MAX; j++) { // j表示列
			c[i][j] = a[i][j] - b[i][j];
		}
	}
	//算乘
	for(int k = 0;k < MAX; k++){//表示前一个数列的列，后一个数列的行
		for (int i = 0; i < MAX; i++) { //i表示行
			for (int j = 0; j < MAX; j++) { // j表示列
				d[i][j] = a[i][k] * b[k][j];
				e[i][j] += d[i][j];
			}
		}
	}
	//输出差
	for(int i = 0;i < MAX; i++){
		for(int j = 0;j < MAX; j++){
			cout << c[i][j] << '\t';
		}
		cout << endl;
	}
	//输出乘积
	for(int i = 0;i < MAX; i++){
		for(int j = 0;j < MAX; j++){
			cout << e[i][j] << '\t';
		}
		cout << endl;
	}
	return 0;
}
