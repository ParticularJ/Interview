class Solution {
public:
	vector<vector<int> >res;
	vector<int> temp;

	void dfs(int index, int sum, int target, vector<int>& candidates) {
		if (index == candidates.size()) {
			if (sum == target)
				res.push_back(temp);
			return;
		}

		int c = candidates[index];

		if (index == (candidates.size() - 1)) {
			if ((target - sum) % c == 0) {
				for (int i = 0; i < (target -sum) / c); i++)
					temp.push_back(c);
				res.push_back(temp);
			}
		}
		else {
			for (;;) {
				dfs(index + 1, sum, target, candidates);
				sum += c;
				temp.push_back(c);
				if (sum > c)
					break;
			}
		}
		while (temp.size() > 0 && temp[temp.size() - 1] == c)
			temp.pop_back();
	}


	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		
		dfs(0, 0, target, vector<int>& candidates);
		return res;
	}
};