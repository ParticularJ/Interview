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

/*
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Note:

All numbers will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: k = 3, n = 7
Output: [[1,2,4]]
Example 2:

Input: k = 3, n = 9
Output: [[1,2,6], [1,3,5], [2,3,4]]
*/


class Solution {
public:
	vector<vector<int> > res;
	void dfs(int sum, int index, int k, int n, int temp) {
		if (sum > n || index == n+1)
			return;
		if (temp.size() == k && sum == n) {
			res.push_back(temp);
			return;
		}
		for (int i = 1; i <= 9; i++) {
			temp.push_back(i);
			dfs(sum + i, i+1, k, n, temp);
			temp.pop_back();
		}

	}

	vector<vector<int> > combinationSum3(int k, int n) {
		res.clear();
		if (k <= 0 || n <= 0)
			return res;
		vector<int> temp;
		dfs(0, 0, k, n, temp);
		return res;
			
	}


};