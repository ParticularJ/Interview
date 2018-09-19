/*
使用滑动窗口，但是，要保证找到的值大于等于v-t, 小于等于 v+t
*/

class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		int size = nums.size();
		set<long long> record;
		for (int i = 0; i < size; i++) {

			// 判断新找的元素的值在set中是否能找到，值的条件满足 大于等于nums[i] -t
			// 小于等于nums[i] + t
			if (record.lower_bound((long long)nums[i] - (long long)t) != record.end() &&
				*(record.lower_bound((long long)nums[i] - (long long)t)) <= (long long)nums[i] + (long long)t)
				return true;
			record.insert(nums[i]);
			if (record.size() == k + 1)
				record.erase(nums[i - k]);
		}
		return false;

	}
};