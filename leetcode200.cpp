/*
联通块， 四联通, 通过递归的方法判断1的块，
*/


class Solution {
public:
	vector<vector<char> > G;
	vector<vector<bool> > flag;
	int row, col;
	void dfs(int i, int j) {
		flag[i][j] = 1;
		int dx[] = { 1, 0 , -1, 0 };
		int dy[] = { 0, 1, 0, -1 };
		for (int p = 0; p < 4; p++) {
			int nx = dx[p] + i;
			int ny = dy[p] + j;
			if (nx >= 0 && nx < row && ny >= 0 && ny < col && G[nx][ny] == '1' && flag[nx][ny]==0) {
				dfs(nx, ny);
			}
		}
	}
	int numIslands(vector<vector<char>>& grid) {
		row = grid.size();
		if (size == 0)return 0;
		col = grid[0].size();
		if (col == 0)return 0;
		G = grid;
		int ret = 0;
		flag = vector<vector<bool> >(row, vector<bool>(col, 0));
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (grid[i][j] == '1' && flag[i][j] == 0) {
					dfs(i, j);
					ret += 1;
				}
			}
		}
		return ret;
	}
};