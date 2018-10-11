class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int> > res(n, vector<int>(n, 0));
		if (n == 0)return res;

		int dr[] = { 0, 1, 0, -1 };
		int dc[] = { 1, 0, -1, 0 };

		for (int row = 0, col = 0, index = 0, number = 1;; number++) {
			res[row][col] = number;
			for (int i = 0; i < 4; i++) {
				int nr = row + dr[index];
				int nc = col + dc[index];
				//  cout<<row<<" "<<col<<endl;
				if (nr >= 0 && nr < n && nc >= 0 && nc < n && res[nr][nc] == 0) {
					row = nr;
					col = nc;
					break;
				}
				// 去下一个位置
				index = (index + 1) % 4;
			}
			if (number == n*n)return res;
		}
	}
};