
//分别去找左右边界

class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int size = nums.size();
		vector<int> res(2, -1);
		int l = 0, r = size - 1;
		for (; l <= r;) {
			int mid = (l + r) >> 1;
			if (nums[mid] < target)l = mid + 1;
			else {
				if (nums[mid] >= target) {
					r = mid - 1;
					if (nums[mid] == target)
						res[0] = mid;
				}
			}
		}
		for (int l = 0, r = size - 1; l <= r;) {
			int mid = (l + r) >> 1;
			if (nums[mid] > target)r = mid - 1;
			else {
				if (nums[mid] <= target) {
					l = mid + 1;
					if (nums[mid] == target)
						res[1] = mid;
				}
			}
		}
		return res;
	}
};

