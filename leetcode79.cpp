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


// Solution2：

/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example:

board =
[
['A','B','C','E'],
['S','F','C','S'],
['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
*/


class Solution {
private:
	// 判断4个方向
	int d[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	int row = 0, col = 0;
	// 回溯法判断有没有走过这个路径
	vector<vector<bool> > visited;

	bool inArea(int x, int y) {
		return x >= 0 && x < row && y < col && y >= 0;
	}
	//从board[x][y]开始，寻找对应的word
	bool searchWord(int x, int y, int index, string& word, vector<vector<char> >& board) {
		// recursive stop conditions
		if (index == word.size()-1) {
			return board[x][y] == word[index];
		}
		// the current word is word[index]
		if (board[x][y] == word[index]) {
			visited[x][y] = true;
			// four direction
			for (int i = 0; i < 4; i++) {
				int newx = x + d[i][0];
				int newy = y + d[i][1];
				if (inArea(newx, newy) && !visited[newx][newy] && searchWord(newx, newy, index + 1, word, board))
					return true;
			}
			visited[x][y] = false;
		}
		return false;
	}

public:
	bool exist(vector<vector<char> >& board, string word) {
		row = board.size();
		col = board[0].size();
		visited = vector<vector<bool>>(row, vector<bool>(col, false));
		if (row == 0 || col == 0)
			return false;
		if (word.size() == 0)
			return false;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (searchWord(i, j, 0, word, board))
					return true;
			}
		}
		return false;
	}
};