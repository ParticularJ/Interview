/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

Example:

Input: n = 4, k = 2
Output:
[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]

*/


class Solution {
public:
	vector<vector<int> > res;
	// index 表示开始的位置
	void dfs(int n, int k, int index, vector<int>& temp) {
		if (index == k) {
			res.push_back(temp);
			return;
		}

		// 优化，我们保证每次有k个元素即可，
		// 则，k-temp.size()说明还有多少个空位, [i,..., n]要有这么多的空位
		// 所以范围为n-(k-temp.size())+1
		for (int i = index; i <= n - (k - temp.size()) + 1; i++) {
			temp.push_back(i+1);
			dfs(n, k, i, temp);
			temp.pop_back();
		}

	}

	vector<vector<int> > combine(int n, int k) {
		if (n <= 0 || k <= 0 || k > n)
			return res;
		vector<int> temp;
		dfs(n, k, 0, temp);
		return res;
	}


};