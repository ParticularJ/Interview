class Solution {
public:
	int sloved(vector<int>& nums, int start, int end) {
		vector<int> memo(end - start + 1, -1);
		memo[0] = nums[start];
		if (memo.size()>1)
			memo[1] = max(nums[start], nums[start + 1]);
		for (int i = start + 2; i <= end; i++) {
			memo[i] = max(nums[i] + memo[i - 2], memo[i - 1]);
		}
		return memo[memo.size() - 1];
	}
	int sloved1(vector<int>& nums, int start, int end) {
		vector<int> memo1(end - start + 1, -1);
		memo1[0] = nums[start];
		if (memo1.size()>1)
			memo1[1] = max(nums[start], nums[start + 1]);
		for (int i = start + 2; i <= end; i++) {
			memo1[i - 1] = max(nums[i] + memo1[i - 3], memo1[i - 2]);
		}
		return memo1[memo1.size() - 1];
	}

	int rob(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)return 0;
		if (size == 1)return nums[0];

		//分段 ： 0-n-1 和 1 - n ,这样就可以避免首尾同时被取到 
		return max(sloved(nums, 0, size - 2), sloved1(nums, 1, size - 1));

	}
};


/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2),
because they are adjacent houses.
Example 2:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

*/
class Solution {
private:
	vector<int> N;
	//[start, end)
	int robToN(int start, int end) {

		vector<int> memo(end - start, -1);
		memo[0] = N[start];
		memo[1] = max(N[start + 1], memo[0]);
		// 范围一定要算好
		// N从start + i开始，因为有偏移量
		for (int i = 2; i < end - start; i++) {
			memo[i] = max(N[start + i] + memo[i - 2], memo[i - 1]);
		}
		return memo[end - start - 1];
	}

public:
	int rob(vector<int>& nums) {
		N = nums;
		int size = nums.size();
		if (size == 0)
			return 0;
		if (size >= 3) {
			int rob1 = robToN(0, size - 1);
			int rob2 = robToN(1, size);
			return rob1 > rob2 ? rob1 : rob2;
		}
		else {
			if (size == 1)
				return nums[0];
			else
				return max(nums[0], nums[1]);
		}

	}
};