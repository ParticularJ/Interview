/*
Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Note:
Each of the array element will not exceed 100.
The array size will not exceed 200.
Example 1:

Input: [1, 5, 11, 5]

Output: true

Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: [1, 2, 3, 5]

Output: false

Explanation: The array cannot be partitioned into equal sum subsets.
*/


class Solution {
private:
	vector<vector<int>> memo;
	bool findPartition(const vector<int>& nums, int index, int sum) {
		if (sum == 0)
			return true;
		if (sum < 0 || index < 0)
			return false;
		if (memo[index][sum] != -1)
			return memo[index][sum] == 1;
		// 类似背包问题，判断需要当前，或者不需要当前
		memo[index][sum] = (findPartition(nums, index - 1, sum) ||
			findPartition(nums, index - 1, sum - nums[index])) ? 1 : 0;
		return memo[index][sum] == 1;
	}

public:
	bool canPartition(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return 0;
		// 判断是否能填满一半即可，能填满一半，那么另一半肯定满足条件
		// 比如 1 5 11 5 ，sum = 22 , sum/2 = 11,
		// 判断能否填满11即可
		int sum = 0;
		for (int i = 0; i < size; ++i) {
			sum += nums[i];
		}
		if (sum % 2 != 0)
			return false;
		memo = vector<vector<int>>(size, vector<int>(sum / 2 + 1, -1));
		return findPartition(nums, size-1, sum / 2);

	}

public:
	bool canPartition1(vector<int>& nums) {
		//动态规划
		int size = nums.size();
		int sum = 0;
		for (int i = 0; i < size; i++) {
			sum += nums[i];
		}
		if (sum % 2 != 0)
			return false;
		int C = sum / 2;
		vector<bool> memo = vector<bool>(C + 1， false);
		for (int i = 0; i < C + 1; i++)
			// 第一行，能放进对应的nums[0]为true
			memo[i] = (nums[0] == i);
		for (int i = 1; i < size; i++)
			for (int j = C; j > nums[i]; j--)
				// 当前已经填满，使用当前，再看memo[j-nums[i]]能不能被填满
				memo[i] = memo[j] || memo[j - nums[i]];
		return memo[C];
	}
};

