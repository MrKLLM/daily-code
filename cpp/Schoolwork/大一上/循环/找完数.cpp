#include<bits/stdc++.h>
using namespace std;

int main(){
	int n=0;
	int sum =0;
	cin >> n;
	for(int i=2;i<n;i++){
		sum=0;
		for(int j =1;j < i;j ++){// 完数从6开始，i从2起步，范围包含n
			if(i%j==0){
				sum+=j;
				// 累加i的所有真约数（1到i-1）
			}
			if(sum > i){// 累加和超过i，提前退出（不可能是完数了）
				break;
			}
		}
		// 所有约数累加完后，再判断是否为完数
		if(sum == i){
			cout << i << " ";
		}
	}
	return 0;
}
