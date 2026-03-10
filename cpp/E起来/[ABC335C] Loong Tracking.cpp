#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int N,Q;
	cin >> N >> Q;
	
	vector<pair<int,int>> pos(N+1);
	for(int i=1;i<=N;i++){
		pos[i] = {i,0};
	}
	
	vector<pair<int,int>> search_pos;
	
	for(int i=0;i<Q;i++){
		int type = 0;
		cin >> type;
		
		
		if(1 == type){
			char dir = 0;
			cin >> dir;
			pair<int,int> old_head = pos[1];//存储旧的头部位置
			//变动头部位置（头部现在的位置）
			if('R' == dir){
				pos[1].first++;
			}else if('L' == dir){
				pos[1].first--;
			}else if('U' == dir){				
				pos[1].second++;
			}else if('D' == dir){
				pos[1].second--;
			}
			//变动头部之后的位置
			for(int j=2;j<=N;j++){
				pair<int,int> old_part_i = pos[j];//存储旧的第i个部分位置
				pos[j] = old_head;//新的第i个部分位置
				old_head = old_part_i;//下一个循环中37行要用
			}
		}else{
			int p = 0;
			cin >> p;
			search_pos.push_back({pos[p].first, pos[p].second});
		}
	}
	
	for(auto& r : search_pos){
		cout << r.first << ' ' << r.second << endl;
	}
	return 0;
}
