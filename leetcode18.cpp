/*
four sum 转化为 3 sum 再转化为 2 sum

*/


class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		vector<vector<int>> res;
		int size = nums.size();
		if (size < 4)return res;
		// sort方便判断
		sort(nums.begin(), nums.end());
		for (int i = 0; i < size; i++) {
			// 固定一位，转换为three sum
			int sum = nums[i];
			for (int j = i + 1; j < size; j++) {
				// 固定两位，转为twosum
				int sum1 = sum + nums[j];
				int front = j;
				int end = size - 1;
				while (front < end) {
					if (sum1 + nums[front] + nums[end] < target)front++;
					else if (sum1 + nums[front] + nums[end] > target)end--;
					else {
						vector<int> temp(4, 0);
						//当前i值
						temp[0] = nums[i];
						//当前j值
						temp[1] = nums[j];
						//front
						temp[2] = nums[front];
						//back
						temp[3] = nums[end];
						res.push_back(temp);
						//去重
						while (front < end&&nums[front] == temp[2])front++;
						while (front < end&&nums[end] == temp[3])end--;
					}
				}
				while (j + 1 < size&&nums[j + 1] == nums[j])j++;
			}
			while (i + 1 < size&&nums[i + 1] == nums[i])i++;
		}
		return res;
	}
};