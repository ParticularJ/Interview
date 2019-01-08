/*
Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.
*/

class Solution {
public:
	int combinationSum4(vector<int>& nums, int target) {
		int size = nums.size();
		if (size == 0)
			return 0;
		sort(nums.begin(), nums.end());
		vector<int> memo(target + 1, 0);
		for(int i=0;i<size;i++)
			for(int j=0;j<target+1;j++)
				memo[j] = max()




	}
};