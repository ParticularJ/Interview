class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		vector<vector<int> > G;
		G = obstacleGrid;
		int row = G.size();
		int col = G[0].size();
		if (row == 0 || col == 0)return 0;

		// 动态规划，维护数组
		vector<vector<int> > f(row, vector<int>(col, 0));
		f[0][0] = G[0][0] != 1;


		for (int i = 0; i<row; i++)
			for (int j = 0; j<col; j++) {
				if (j + 1<col && G[i][j + 1] != 1)
					f[i][j + 1] += f[i][j];
				if (i + 1<row && G[i + 1][j] != 1)
					f[i + 1][j] += f[i][j];
			}
		return f[row - 1][col - 1];
	}
};