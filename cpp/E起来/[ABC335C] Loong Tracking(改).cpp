#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	int N, Q;
	cin >> N >> Q;
	
	//存储头部的移动轨迹
	vector<pair<int, int>> head_pos;
	head_pos.push_back({1, 0});
	
	vector<pair<int, int>> search_pos;
	
	for(int i=0; i<Q; i++){
		int type;
		cin >> type;
		
		if(type == 1){//移动头部
			char dir;
			cin >> dir;
			//获取头部当前位置轨迹的最后一个元素）
			auto [x, y] = head_pos.back();
			//更新头部位置
			if(dir == 'R') x++;
			else if(dir == 'L') x--;
			else if(dir == 'U') y++;
			else if(dir == 'D') y--;
			//将新位置加入轨迹
			head_pos.push_back({x, y});
		}else{//查询部位p
			int p;
			cin >> p;
			int k = head_pos.size() - 1;//头部移动的总步数
			int idx = k - (p - 1);//推导部位p对应的头部轨迹索引
			pair<int, int> res;
			if(idx >= 0){
				res = head_pos[idx];//从轨迹中取位置
			}else{
				res = {p, 0};//步数不足，初始位置
			}
			search_pos.push_back(res);//存储结果
		}
	}
	
	for(auto& r : search_pos){
		cout << r.first << ' ' << r.second << endl;
	}
	return 0;
}
