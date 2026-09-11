#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
#define DEBUG (0)
#endif

const int MAXQ = 200005;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n,q;
	cin >> n;
	vector<long long > arr(n+1);//存值
	vector<int> last_time(n+1,0);//存最后修改时间
	
	long long  global_val = 0;
	int global_time = -1;
	
	for(int i=1;i<=n;i++){
		long long  tmp;
		cin >> tmp;
		arr[i] = tmp;
	}
	
	cin >> q;
	for(int time = 1; time <= q; time++){
		long long  op,i;
		int k;
		cin >> op;
		switch (op) {
		case 1:
			cin >> k;
			global_val = k;
			global_time = time;
			break;
		case 2:
			cin >> i >>k;
			
			long long  curr_val;
			if(last_time[i] > global_time){
				curr_val = arr[i]+k;
			}else{
				curr_val = global_val+k;
			}
			arr[i] = curr_val;
			last_time[i] = time;
			break;
		case 3:
			cin >> i;
			if(last_time[i] > global_time){
				cout << arr[i] << endl;
			}else{
				cout << global_val << endl;
			}
			break;
		}
	}
	return 0;
}
