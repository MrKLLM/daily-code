#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif

int main() {
	int n;
	cin >> n;
	queue<int> q;
	stack<int> s;
	for(int i=0;i<n;i++){
		int a = 0;
		cin >> a;
		q.push(a);
	}
	
	for(int i=0;i<n;i++){
		int tmp = q.front();
		q.pop();
		s.push(tmp);
	}
	
	while(!s.empty()){
		cout << s.top() << ' ';
		if(!s.empty()){
			s.pop();
		}
	}
	return 0;
}
