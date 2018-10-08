/*
   根据题意，枚举,因为 size不超过20，所以有枚举的可能，2^20次方
   但是枚举TLE，所以二分变成 2^10 * 2
*/


class Solution {
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		int size = nums.size();
		int res = 0;

		// 使用map完成折半
		unordered_map<int, int> mymap;
		int left_size = size / 2;
		int right_size = size - left_size;

		for (int i = 0; i < (1 << left_size); i++) {
			int sum = 0;
			for (int j = 0; j < left_size; j++) {
				//判断位置，使得每次不同的点取得不同的符号
				if (i&(1 << j))
					sum += nums[j];
				else
					sum -= nums[j];
			}
				mymap[sum]++;
		}

		for (int i = 0; i < right_size; i++) {
			int sum = 0;
			for (int j = 0; j < right_size; j++) {
				//判断位置，使得每次不同的点取得不同的符号
				if (i&(1 << j))
					sum += nums[left_size + j];
				else
					sum -= nums[left_size + j];
			}
			res += mymap[S-sum];
		}
		return res[S];
	}
};