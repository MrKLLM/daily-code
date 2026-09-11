#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif
int main(){
	int n = 0;
	cin >> n;
	
	int* prime = new int[n]{0};
	int prime_sum = 0;
	int k = 0;
	for(int i=0;i<=(n-1);i++){
		int a = 0;
		cin >> a;
		if (a <= 1 || a % 2 == 0) {//排除掉1和2以外的偶数
			continue;
		}
		if (a == 2 ) {//2是质数
			prime[k] = a;
			prime_sum +=a;
			k++;
			continue;
		}
		
		bool is_prime = true;
		for (int j = 3; j <= sqrt(a); j += 2) {//遍历到a的开方为止的奇数作为因数检查数a是否有因数
			if (a % j == 0) {//有因数
				is_prime = false;
				break;
			}
		}
		if (is_prime){//是素数，收入数组中
			prime[k] = a;
			prime_sum +=a;
			k++;
		}
	}
	
	cout << prime_sum << endl;
	//下面是排序
	sort(prime,prime+k,greater<int>());
	
	for(int i=0;i<=(k-1);i++){
		cout << prime[i] << ' ';
	}
	
	delete[] prime;
	return 0;	
}
