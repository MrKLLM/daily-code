#include<bits/stdc++.h>
using namespace std;

int max_public_yue(int a, int b) {
	int max_yue = 0;
	int min_value = min(a, b);
	for (int i = 1; i <= min_value; i++) {
		if ((a % i == 0) && (b % i == 0)) {
			if(i > max_yue){
				max_yue = i;
			}
		}
	}
	return max_yue;
}
int min_public_bei(int a, int b) {
	int max_value = max(a, b);
	for (int i = max_value; i <= (a*b); i++) {
		if ((i % a == 0) && (i % b == 0)) {
			return i;
		}
	}
	return -1;
}
int main() {
	int m, n;
	cin >> m >> n;
	int max_yue = max_public_yue(m,n);
	int min_bei = min_public_bei(m,n);
	cout << max_yue << ' ' << min_bei;
	return 0;
}

