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
		// ���Ʊ������⣬�ж���Ҫ��ǰ�����߲���Ҫ��ǰ
		memo[index][sum] = (findPartition(nums, index - 1, sum) ||
			findPartition(nums, index - 1, sum - nums[index])) ? 1 : 0;
		return memo[index][sum] == 1;
	}

public:
	bool canPartition(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return 0;
		// �ж��Ƿ�������һ�뼴�ɣ�������һ�룬��ô��һ��϶���������
		// ���� 1 5 11 5 ��sum = 22 , sum/2 = 11,
		// �ж��ܷ�����11����
		int sum = 0;
		for (int i = 0; i < size; ++i) {
			sum += nums[i];
		}
		if (sum % 2 != 0)
			return false;
		memo = vector<vector<int>>(size, vector<int>(sum / 2 + 1, -1));
		return findPartition(nums, size-1, sum / 2);

	}
};

