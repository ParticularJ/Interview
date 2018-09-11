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