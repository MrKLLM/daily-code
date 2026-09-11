#include<bits/stdc++.h>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	int min_val = min(a, b);
	for (int i = min_val ; i < a / 2 ; --i) {
		if (!(a % i)
		    && !(b % i)) {
			cout << i << " " ;
			break;
		}
	}
	for (int n = min_val ; n < a * b; n++) {
		if ((n % a == 0)
		    && (n % b == 0)) {
			cout << n;
			break;
		}
	}
	return 0;
}
