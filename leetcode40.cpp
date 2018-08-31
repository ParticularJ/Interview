class Solution {
public:
	vector<vector<int>> res;
	vector<int> temp;
	void dfs(int index, int target, int sum, vector<int>& cand) {
		if (index == cand.size()) {
			if (sum == target) {
				res.push_back(temp);
			}
			return;
		}
		int i = index;
		for (; i + 1<cand.size() && cand[i + 1] == cand[index]; i++);
		//通过此来计算一个字母出现多少次，从而循环多少次，这样每个字母就不会重复取
		int total = i - index + 1;
		for (int j = 0; j <= total; j++) {
			dfs(index + total, target, sum, cand);
			temp.push_back(cand[index]);
			sum += cand[index];
			if (sum > target)
				break;
		}
		while (temp.size() > 0 && temp[temp.size() - 1] == cand[index])
			temp.pop_back();
	}



	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		//int size = candidates.size();
		sort(candidates.begin(), candidates.end());
		dfs(0, target, 0, candidates);
		return res;
	}
};