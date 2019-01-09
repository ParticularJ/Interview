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
		// ��ʼ������
		vector<int> memo(target + 1, 0);
		memo[0] = 1;

		for (int i = 1; i < target+1; i++)
			for (int j = 0; j < size; j++)
				if (i >= nums[j])
					// ģ�ⱳ��������1�ĸ���λ1
					// ����2 ����Ϊ 1 1 ��  2 0
					// memo[2] = memo[2] + memo[2-1]
					// memo[2] = memo[2] + memo[2-2]
					// ��������
					memo[j] += memo[j - nums[i]];

		return memo[target];




	}
};