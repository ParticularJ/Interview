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

/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1
Example 2:

Input:
11000
11000
00100
00011

Output: 3

*/

class Solution {
private:
	int row = 0, col = 0;
	int d[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };
	vector<vector<bool> > visited;
	bool inArea(int x, int y) {
		return x >= 0 && x < row&&y >= 0 && y < col;
	}

	void floodfill(int x, int y, vector<vector<char> >& grid) {
		visited[x][y] = true;
		for (int i = 0; i < 4; i++) {
			int newx = x + d[i][0];
			int newy = y + d[i][1];
			// 暗含递归终止条件
			if (inArea(newx, newy) && !visited[newx][newy] && grid[newx][newy] == '1')
				floodfill(newx, newy, grid);
		}
		return;
	}

public:
	int numIslands(vector<vector<char>>& grid) {
		row = grid.size();
		if (row == 0)
			return 0;
		col = grid[0].size();
		if (col == 0)
			return 0;
		visited = vector<vector<bool> >(row, vector<bool>(col, false));

		if (row == 0 || col == 0)
			return 0;
		int res;
		
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				// 当前是陆地且没有遍历过
				if (grid[i][j] == '1' && !visited[i][j]) {
					res++;
					//扩充
					floodfill(i, j, grid);
				}
			}
		}
		return res;
	}
};
