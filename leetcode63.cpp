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


/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?



An obstacle and empty space is marked as 1 and 0 respectively in the grid.

Note: m and n will be at most 100.

Example 1:

Input:
[
[0,0,0],
[0,1,0],
[0,0,0]
]
Output: 2
Explanation:
There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
*/

class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		int row = obstacleGrid.size();
		int col = obstacleGrid[0].size();
		assert(row > 0 && col > 0);
		vector<vector<int> > memo(row, vector<int>(col, 0));

		// 遇到障碍使得第一行和第一列剩余位置为0
		for (int i = 0; i < row; i++) {
			if (obstacleGrid[i][0] != 1)
				memo[i][0] = 1;
			else 
				break;
		}

		for (int j = 0; j < col; j++) {
			if (obstacleGrid[0][j] != 1)
				memo[0][j] = 1;
			else
				break;
		}

		for(int i=1;i<row;i++)
			for (int j = 1; j < col; j++) {
				if (obstacleGrid[i][j] == 1) {
				}
				else {
					memo[i][j] = memo[i - 1][j] + memo[i][j - 1];
				}
			}
		return memo[row - 1][col - 1];
	}
};
