class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		int size = triangle.size();
		if (size == 0)return 0;
		
		for (int i = 1; i < size; i++) {
			// 每一行第一个，只是上一行的累加
			triangle[i][0] += triangle[i - 1][0];
			triangle[i][i] += triangle[i - 1][i - 1];
			for (int j = 1; j < i; j++) {
				triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
			}
		}

		return *min_element(triangle[size-1].begin(), triangle[size-1].end());
	}
};

/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
[2],
[3,4],
[6,5,7],
[4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
*/

class Solution {
public:
	int minimumTotal(vector<vector<int> >& triangle) {
		// 求最小值
		int res = INT_MAX;
		int row = triangle.size();
		if (row == 0)
			return 0;
		// 先记录第一列以及每一行的最后一列
		for (int i = 1; i < triangle.size(); i++) {
			triangle[i][0] += triangle[i - 1][0];
			triangle[i][i] += triangle[i - 1][i - 1];
			// 使用动态规划计算中间列
			for (int j = 1; j < triangle[i].size() - 1; j++) {
				triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
			}
		}
		// 计算最小值
		for (int k = 0; k < triangle[row - 1].size(); k++) {
			res = min(res, triangle[row - 1][k]);
		}
		return res;
	}
};