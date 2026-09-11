#include <bits/stdc++.h>
using namespace std;
double func(int a, int b, int& geshu) {
	double pingjun = 0;
	bool find = false;
	int sum = 0;
	for (int i = a; i <= b; i++) {
		//先考虑2的情况
		if(i == 2){
			sum += i;
			geshu ++;
			find = true;
			continue;
		}
		
		if ((i == 1) || (i % 2 == 0)) {
			continue;
		} else {
			for (int j = 3; j <= i; j += 2) {
				bool is_prime = true;
				if (j != i && i % j == 0) {
					is_prime = false;
					break;
				} else if (j == i && is_prime) {
					sum += i;
					geshu ++;
					find = true;
				}
			}
		}
	}
	
	if(!find){
		return -1.0;
	}
	pingjun = (sum * 1.0) / (geshu*1.0);
	
	return pingjun;
}
int main() {
	int m, n;
	cin >> m >> n;
	int geshu = 0;
	double pingjun_val = 0;

	pingjun_val = func(m, n, geshu);
	if(pingjun_val == -1.0){
		cout << "no";
		return 0;
	}else{
		cout << geshu << ' ' << pingjun_val;
	}
}
