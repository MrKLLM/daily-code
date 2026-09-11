#include <iostream>
#include <vector>
using namespace std;

int main() {
	int H, W, N;
	cin >> H >> W >> N;
	
	// 初始化网格，全部为白色（.）
	vector<vector<char>> grid(H, vector<char>(W, '.'));
	
	// 方向：上、右、下、左，对应移动的偏移量（di, dj）
	int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	int dir = 0; // 初始方向向上
	
	int i = 0, j = 0; // 初始位置（1,1）对应0-based索引（0,0）
	
	for (int step = 0; step < N; ++step) {
		if (grid[i][j] == '.') {
			// 当前为白色，涂成黑色，顺时针旋转90度
			grid[i][j] = '#';
			dir = (dir + 1) % 4;
		} else {
			// 当前为黑色，涂成白色，逆时针旋转90度
			grid[i][j] = '.';
			dir = (dir + 3) % 4; // 等价于dir-1 mod 4
		}
		
		// 移动到新位置，处理环面结构
		i = (i + dirs[dir][0] + H) % H;
		j = (j + dirs[dir][1] + W) % W;
	}
	
	// 输出网格
	for (int row = 0; row < H; ++row) {
		for (int col = 0; col < W; ++col) {
			cout << grid[row][col];
		}
		cout << endl;
	}
	
	return 0;
}
