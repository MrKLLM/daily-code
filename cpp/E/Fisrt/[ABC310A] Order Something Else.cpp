#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, p, q;
	cin >> n >> p >> q;

	vector<int> d;
	for (int i = 0; i < n; i++) {
		int a = 0;
		cin >> a;
		d.push_back(a);
	}

	vector<int>:: iterator cheapest_price_addr = min_element(d.begin(), d.end()); //返回值类型迭代器（iterator）,注意迭代器所在空间
	int cheapest_price = *cheapest_price_addr;
	if (cheapest_price + q < p) {
		cout << cheapest_price + q;
	} else {
		cout << p;
	}
	return 0;
}
