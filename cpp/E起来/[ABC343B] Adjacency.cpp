#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int N = 0;
	cin >> N;
	vector <vector <int>> records;//开个二维动态数组记录1的列号，外层（即records）管行，内层管1的列号
	
	for(int i=0;i<N;i++){
		vector <int> row_records;//记录1的列号（被records管）
		for(int j=0;j<N;j++){
			int point = 0;
			cin >> point;
			if(point==1){
				row_records.push_back(j+1);//位置是从1开始索引的
			}
		}
		records.push_back(row_records);//把row_records的辛勤成果收做自己一个元素，row_records哭哭
	}
	
	for(auto &per_row : records){//&per_row is copyvalue,是个一维数组
		for(long long unsigned int k=0;k<per_row.size();k++){//记住size返回类型为long long unsigned int啊
			if(k>0){
				cout << ' ';
			}
			cout << per_row [k];
		}
		cout << endl;
	}
	return 0;
}
