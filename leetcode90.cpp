/*
ö�����з���,��λ�ķ���
*/

class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		vector<vector<int> > res;
		int size = nums.size();
		sort(nums.begin(), nums.end());
		// mapȥ��
		unordered_map<vector<int>, int> flag;
		for (int i = 0; i < (1 << size); i++) {
			vector<int> temp;
			for (int j = 0; j < size; j++) {
				//ͨ����λ��ķ�����ö�����е�����
				if (i&(1 << j))
					temp.push_back(nums[j]);
			}
			if (flag[temp] == 0) {
				res.push_back(temp);
				//flag[temp] = 1;
			}
		}
		return res;
	}
};

class Solution {
public:
	vector<vector<int> > res;
	void dfs(int index, vector<int>& nums, vector<int>& temp) {
		res.push_back(temp);
		for (int i = index; i < nums.size(); i++) {
			if (i > index && nums[i - 1] == nums[i])
				continue;
			temp.push_back(nums[i]);
			dfs(i + 1, nums, temp);
			temp.pop_back();
		}
	}
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		int size = nums.size();
		sort(nums.begin(), nums.end());
		if (size == 0)
			return res;
		vector<int> temp;
		dfs(0, nums, temp);
		return res;
	}
};

