class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		int size = triangle.size();
		if (size == 0)return 0;
		
		for (int i = 1; i < size; i++) {
			// ÿһ�е�һ����ֻ����һ�е��ۼ�
			triangle[i][0] += triangle[i - 1][0];
			triangle[i][i] += triangle[i - 1][i - 1];
			for (int j = 1; j < i; j++) {
				triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
			}
		}

		return *min_element(triangle[size-1].begin(), triangle[size-1].end());
	}
};