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
				flag[temp] = 1;
			}
		}
		return res;
	}
};