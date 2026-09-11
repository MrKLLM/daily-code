#include<iostream>

using namespace std;

#ifndef MAX
	#define MAX (100)
#endif

int main(){
	int m,n;
	cin >> m >> n;
	int arr[MAX][MAX];
	//输入矩阵
	for(int i=0;i<m;i++){
		
		for(int q=0;q<n;q++){
			int a = 0;
			cin >> a;
			arr[i][q] = a;
		}
	}
	
	int x,y,j,k;
	cin >> x >> y >> j >> k;
	if((x+j>m) || (y+k>n)){
		cout << "para error";
	}else{
		//输出子矩阵
		for(int i=x;i<x+j;i++){
			for(int q=y;q<y+k;q++){
				cout << arr[i][q] << ' ';
			}
			cout << endl;
		}
		
	}
}

