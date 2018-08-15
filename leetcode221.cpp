/*
动态规划：统计上方和左方的值是否为相等，若为1，则再判断左上方的数值比如
模拟：
 一大一小  4444   相等：     ?4444  
          4444              44444
          3334              44444              如果一大一小，肯定可以扩展成min+1;
          3334              44444              如果两个相等，则判断左上角(?)是否为1，是1加1，否则不加
          333X              4444X
*/

class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		row = matrix.size();
		if (row == 0)return 0;
		col = matrix[0].size();
		if (col == 0)return 0;
		int res = 0;
		vector<vector<int> > dist(row, vector<int>(col, 0));

		// 统计第一行和第一列的距离
		for (int i = 0; i < row; i++) {
			if (matrix[i][0] == '1')
				dist[i][0] = 1;
		}
		
		for (int j = 0; j < col; j++) {
			if (matrix[0][j] == "1")
				dist[0][j] = 1;
		}

		for (int i = 1; i < row; i++) {
			for (int j = 1; j < col; j++) {
				if (matrix[i][j] == '1') {
					int left = matrix[i - 1][j];
					int up = matrix[i][j - 1];
					if (left != up) {
						dist[i][j] = min(left, up)+1;
					}
					else
						dist[i][j] = up + (matrix[i - left][j - up] == "1");
				}
			}
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				res = max(res, dist[i][j]);
			}
		}
		return res;
	}
};