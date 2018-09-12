class Solution {
public:
	vector<vector<int> > res;
	vector<int> temp;
	void dfs(int dep, int total, int maxi, int sum) {
		if (total > sum)
			return;
		if (dep == maxi && total == sum) {
			res.push_back(temp);
			return;
		}

		int last = dep == 0 ? 0 : temp[dep - 1];
		for (int i = last + 1; i < 10; i++) {
			temp.push_back(i);
			dfs(dep + 1, total + i, maxi, sum);
			temp.pop_back();
		}
	}

	vector<vector<int>> combinationSum3(int k, int n) {
		// 记录当前个数， 当前总和， 期望数字个数， 期望和
		dfs(0, 0, k, n);
		return res;
	}
};