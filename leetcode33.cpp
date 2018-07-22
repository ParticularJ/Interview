/*
思路： 使用二分，找到规律， 记得加"="号

*/
class Solution {
public:
	int search(vector<int>& nums, int target) {
		int size = nums.size();
		if (size == 0)return -1;

		for (int l = 0, r = size - 1; ;) {
			int mid = (l + r) >> 1, numm = nums[mid];
			if (target == numm)return mid;
			int numl = nums[l], numr = nums[r];

			if (numl <= numm && numm <= numr) {
				for (int L = l, R = r; L <= R;) {
					mid = (L + R) >> 1;
					if (target == nums[mid])return mid;
					else if (target > nums[mid])
						L = mid + 1;
					else
						R = mid - 1;
				}
				return -1;  
			}
			if (numm >= numl && numm >= numr) {
				if (target <= numm&&target >= numl) {
					r = mid - 1;
				}
				else 
					l = mid + 1;
				
			}
			if (numm <= numl&&numm <= numr) {
				if (target >= numm&&target <= numr) {
					l = mid + 1;
				}
				else 
					r = mid - 1;
				
			}
		}
		return -1;
	}
};