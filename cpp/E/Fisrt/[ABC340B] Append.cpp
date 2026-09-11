#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int Q = 0;
	cin >> Q;
	vector <int> A;
	vector <int> elem ;
	
	
	for(int i=0;i<Q;i++){
		int query_type = 0;
		cin >> query_type;
		
		if(1 == query_type){
			int x = 0;
			cin >> x;
			A.push_back(x);
		}else{
			int k = 0;
			cin >> k;
			elem.push_back(*(A.rbegin()+(k-1)));
		}
	}
	
	for(auto a : elem){
		cout << a << endl;
	}
	return 0;
}
