/*
set 的用法，
只存储不同的元素
*/

class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		int size = nums.size();
		set<int> record;
		// 维持一个k大小的滑动窗口
		for (int i = 0; i < nums.size(); i++) {
			if (record.find(nums[i]) != record.end())
				return true;
			record.insert(nums[i]);

			// 维持长度为k
			if (record.size() == k + 1)
				record.erase(nums[i - k]);
		}
		
		return false;
	}
};