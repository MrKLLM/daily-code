#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
#define DEBUG (0)
#endif

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	vector<vector<int> > spiral_matrix(n, vector<int>(n,0));

	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};
	
	int x = 0, y = 0;
	int dir = 0;
	for (int i = 1; i <= n * n; i++) {
		spiral_matrix[x][y] = i;
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		//判断是否撞墙
		if (nx < 0 || nx >= n || ny < 0 || ny >= n || spiral_matrix[nx][ny] != 0) {
			dir =( dir + 1)%4;//右转
			nx = x + dx[dir];
			ny = y + dy[dir];
		}
		x = nx;
		y = ny;
	}
	//输出
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << spiral_matrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
