/*
Ä£ÄâÂÝÐý
*/
class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> res;
		int row = matrix.size();
		if (row == 0)return res;
		int col = matrix[0].size();
		if (col == 0)return res;
		vector<vector<bool> > flag(row, vector<bool>(col, 0));

		int dx[] = { 0, 1, 0, -1 };
		int dy[] = { 1, 0, -1, 0 };
		
		for (int r = 0, c = 0, index = 0; ;) {
			flag[r][c] = 1;
			res.push_back(matrix[r][c]);
			int index = 0;
			for (int i = 0; i < 4; i++) {
				int succ = 0;
				int nx = r + dx[index];
				int ny = r + dy[index];
				if (nx >= 0 && nx < row && ny >= 0 && ny < col && flag[nx][ny] == 0) {
					r = nx;
					c = ny;
					succ = 1;
					break;
				}
				else {
					index = (index + 1) % 4;
				}
			}
			if (succ == 0)break;
		}
		return res;
	}
};