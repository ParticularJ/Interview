/*
dfs 列举所有可能，超时
*/


class Solution {
public:
	vector<int> memo;
	void dfs(vector<int>& nums, int index, int dep, int sum) {
		if (dep == 3) {
			// cout<<sum<<" ";
			memo.push_back(sum);
			return;
		}
		if (index == nums.size())
			return;
		for (; index<nums.size(); index++) {
			sum = sum + nums[index];
			dfs(nums, index + 1, dep + 1, sum);
			sum = sum - nums[index];
		}
	}

	int threeSumClosest(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		if (nums.size()<3)return 0;

		dfs(nums, 0, 0, 0);

		int maxi = (1ll << 31) - 1;
		int res = 0;
		sort(memo.begin(), memo.end());
		for (int i = 0; i<memo.size(); i++) {
			if (abs(memo[i] - target)<maxi) {
				res = memo[i];
				maxi = abs(memo[i] - target);
			}
		}

		return res;
	}
};




class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		int res = 0;
		int maxi = (1ll << 31) - 1;
		for (int i = 0; i < nums.size(); i++) {
			int temp1 = nums[i];
			int l = i + 1, r = nums.size()-1;
			while (l < r) {
				if (temp1 + nums[l] + nums[r] == target)
					return target;
				else {
					if (abs(temp1 + nums[l] + nums[r] - target) < maxi) {
						res = temp1 + nums[l] + nums[r];
						maxi = abs(temp1 + nums[l] + nums[r] - target);
					}
					if (temp1 + nums[l] + nums[r] > target)
						r--;
					else
						l++;
				}
			}
		}
		return res;
	
	}


};