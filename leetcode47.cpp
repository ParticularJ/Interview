/*
˼�룬����֮�󣬲�ͣ������ֱ����������
*/

class Solution {
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int> > res;
		int size = nums.size();
		sort(nums.begin(), nums.end());
		while (1) {
			res.push_back(nums);
			if (size == 0)return res;
			// ����ѭ������������Ӵ�С�Ѿ����к�
			int ascend = size - 1;
			while (ascend != 0 && nums[ascend - 1] >= nums[ascend])
				ascend--;
			if (ascend == 0)
				break;

			//���������λ
			int mini = nums[ascend-1];
			for (int i = size - 1; i >= ascend; i--) {
				if (nums[i] > mini) {
					swap(nums[i], nums[ascend-1]);
					break;
				}
			}
			// ��ascend���󣬽���˳��,ȷ��������ǰ����
			// ��Ϊ��ͨ����һ��������������123��һ�����ȵõ�321������
			// �ͻ�ȱ��312�� ����Ҫ�Ƚ�ascend������н�����
			for (int i = ascend, j = size - 1; i <= j; i++, j--) {
				swap(nums[i], nums[j]);
			}
		}
		return res;
	}
};