/*
set 的用法，
只存储不同的元素
*/

class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		int size = nums.size();
		set<int> s;
		if (size == 0)return false;
		int K = min(size-1, k);
		for (int i = 0; i <= K; i++) {
			if (s.find(nums[i])!=s.end())
				return true;
			s.insert(nums[i]);
		}
		for (int i = k; i < size; i++) {
			// 动态维护k长度的set
			s.erase(nums[i - k -1]);
			// 找到了
			if (s.find(nums[i])!=s.end())
				return true;
			s.insert(nums[i]);
		}
		return false;
	}
};