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

/*
Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of times.

Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
[7],
[2,2,3]
]
Example 2:

Input: candidates = [2,3,5], target = 8,
A solution set is:
[
[2,2,2,2],
[2,3,3],
[3,5]
]
*/

class Solution {
public:
	vector<vector<int> > res;
	void dfs(vector<int>& cand, int index, int sum, int target, vector<int>& temp) {
		if (sum == target) {
			res.push_back(temp);
			return;
		}
		if (sum > target)
			return;
		for (int i = index; i < cand.size(); i++) {
			temp.push_back(cand[i]);
			dfs(cand, i, sum + cand[i], target, temp);
			temp.pop_back();
		}

	}
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<int> temp;
		sort(candidates.begin(), candidates.end());
		dfs(candidates, 0, 0, target, temp);
		return res;
	}


};
