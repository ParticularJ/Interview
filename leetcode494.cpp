/*
   �������⣬ö��,��Ϊ size������20��������ö�ٵĿ��ܣ�2^20�η�
   ����ö��TLE�����Զ��ֱ�� 2^10 * 2
*/


class Solution {
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		int size = nums.size();
		int res = 0;

		// ʹ��map����۰�
		unordered_map<int, int> mymap;
		int left_size = size / 2;
		int right_size = size - left_size;

		for (int i = 0; i < (1 << left_size); i++) {
			int sum = 0;
			for (int j = 0; j < left_size; j++) {
				//�ж�λ�ã�ʹ��ÿ�β�ͬ�ĵ�ȡ�ò�ͬ�ķ���
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
				//�ж�λ�ã�ʹ��ÿ�β�ͬ�ĵ�ȡ�ò�ͬ�ķ���
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