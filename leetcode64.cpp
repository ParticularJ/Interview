/*
最短路径问题，使用SPFA
*/ 
class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int row = grid.size();
		if (row == 0)return 0;
		int col = grid[0].size();
		if (col == 0)return 0;
		
		queue<pair<int, int>> que;
		que.push(make_pair(0, 0));
		vector<vector<int> > dist(row, vector<int>(col, ((1 << 31) - 1)));
		vector<vector<int> > inqueue(row, vector<int>(col, 0));
		inqueue[0][0] = 1;
		dist[0][0] = grid[0][0];

		int dx[] = { 0, 1 };
		int dy[] = { 1, 0 };
		for (; que.size() > 0;) {
			auto front = que.front();
			que.pop();
			for (int i = 0; i < 2; i++) {
				int nx = front.first + dx[i];
				int ny = front.second + dy[i];
				if (nx < row && ny < col) {
					if (dist[nx][ny] > dist[nx][ny] + grid[front.first][front.second]) {
						dist[nx][ny] = dist[nx][ny] + grid[front.first][front.second];
					}
					if (inqueue[nx][ny] == 0) {
						inqueue[nx][ny] = 1;
						que.push(make_pair(nx, ny));
					}
				}
			}
		}
		return dist[row - 1][col - 1];
	}
};

/*
64. Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

Input:
[
[1,3,1],
[1,5,1],
[4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.
*/


// space O(1)
// time O(n^2)
class Solution {
public:
	int minPathSum(vector<vector<int>>& board) {
		int row = board.size();
		if (row == 0)
			return 0;
		int col = board[0].size();
		if (col == 0)
			return 0;
		// 初始化 行和列
		for (int i = 1; i < row; i++)
			board[i][0] += board[i - 1][0];
		for (int j = 1; j < col; j++)
			board[0][j] += board[0][j - 1];

		// 动态规划，选择最小值
		for (int i = 1; i < row; i++)
			for (int j = 1; j < col; j++)
				board[i][j] += min(board[i - 1][j], board[i][j - 1]);

		return board[row - 1][col - 1];
	}
};



// space O(n)
// time O(n ^ 2)
class Solution {
public:
	int minPathSum(vector<vector<int>>& board) {
		int row = board.size();
		if (row == 0)
			return 0;
		int col = board[0].size();
		if (col == 0)
			return 0;
		// space O(n)
		vector<int> memo(col, 0);
		memo[0] = board[0][0];
		// 初始化第一行
		for (int i = 1; i < col; i++)
			memo[i] = board[0][i] + memo[i-1];
		// 从第一行开始
		for (int i = 1; i < row; i++) {
			// 更新memo[0]
			memo[0] += board[i][0];
			for (int j = 1; j < col; j++) {
				// 计算剩余的memo
				memo[j] = min(memo[j - 1] + board[i][j], memo[j] + board[i][j]);
			}
		}
		return memo[col-1];
	}
};

