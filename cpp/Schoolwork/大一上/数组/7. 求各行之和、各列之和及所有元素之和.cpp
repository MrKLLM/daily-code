#include<bits/stdc++.h>
using namespace std;

int main(){
	int m ,n;
	cin >> m >> n;
	int matrix[10][10];
	int row_sums = 0;
	int column_sums = 0;
	int all_elements_sums = 0;
	
	for(int i=0;i<=(m-1);i++){
		
		for(int j=0;j<=(n-1);j++){
			int a = 0;
			cin >> a;
			matrix[i][j] = a;
			
			all_elements_sums+= a;
		}
	}
	
	for(int i=0;i<=(m-1);i++){
		row_sums = 0;
		for(int j=0;j<=(n-1);j++){
			row_sums += matrix[i][j];
		}
		cout << row_sums << ' ';
	}
	cout << endl;
	
	for(int j=0;j<=(n-1);j++){
		column_sums = 0;
		for(int i=0;i<=(m-1);i++){
			column_sums += matrix[i][j];
		}
		cout << column_sums << ' ';
	}
	cout << endl;
	
	cout << all_elements_sums;
	return 0;
}
