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