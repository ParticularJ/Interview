/*
搜索问题，dfs
用数组flag表示是否遍历过
*/


class Solution {
public:
	int row, col;
	bool res;
	vector<vector<char> > b;
	int flag[1000][1000];

	void dfs(int x, int y, int index, string& word) {
		if (index == word.size()) {
			res = 1;
			return;
		}
		if (res)return;
		int dx[] = { 0, 1, 0 , -1 };
		int dy[] = { 1, 0, -1, 0 };
		for (int i = 0; i < 4; i++) {
			int nx = dx[i] + x;
			int ny = dy[i] + y;
			if (nx >= 0 && nx < row && ny >= 0 && ny < col && flag[nx][ny] == 0 && word[index] == b[nx][ny]) {
				flag[nx][ny] = 1;
				dfs(nx, ny, index + 1, word);
				flag[nx][ny] = 0;
			}
		}
	}


	bool exist(vector<vector<char>>& board, string word) {
		b = board;
		row = board.size();
		if (row == 0)return false;
		col = board[0].size();
		if (col == 0)return false;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				flag[i][j] = 0;
			}
		}


		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (word[0] == board[i][j] && res == 0) {
					flag[i][j] = 1;
					dfs(i, j, 1, word);
					flag[i][j] = 0;
				}
			}
		}
		return res;
	}
};