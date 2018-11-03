/*
Given a collection of distinct integers, return all possible permutations.

Example:

Input: [1, 2, 3]
	Output :
	[
		[1, 2, 3],
		[1, 3, 2],
		[2, 1, 3],
		[2, 3, 1],
		[3, 1, 2],
		[3, 2, 1]
	]
*/


class Solution {
public:
	vector<vector<int> > res;
	vector<bool> flag;
	void __permute(vector<int>& nums, int index, vector<int>& temp) {
		if (index == nums.size()) {
			res.push_back(temp);
			return;
		}
		
		for (int i = 0; i < nums.size(); i++) {
			if (!flag[i]) {
				temp.push_back(nums[i]);
				flag[i] = true;
				__permute(nums, index + 1, temp);
				temp.pop_back();
				flag[i] = false;
			}
		}
	}

	vector<vector<int> > permute(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return res;
		flag = vector<bool>(size, 0);
		vector<int> temp;
		__permute(nums, 0, temp);
		return res;
	}
};