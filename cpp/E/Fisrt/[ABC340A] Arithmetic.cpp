#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int a,b,d;
	cin >> a >> b >> d;
	int next_item = 0;
	int n = 1;
	while(b > next_item){
		next_item = a + (n-1)*d;
		cout << next_item << ' ';
		n++;
	}
	return 0;
}
