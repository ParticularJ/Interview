/*
ά������λ�ã�
*/

class Solution {
public:
	int get_next(vector<int>& nums, int index) {
		for (int i = index; i < nums.size(); i++) {
			if (nums[i] != nums[index])
				return i;
		}
		return nums.size();
	}

	int removeDuplicates(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)return 0;
		int k = 0;
		for (int i = 0; i < size;) {
			//���ص�һ������ȵ�λ��
			int index = get_next(nums, i);
			// ���ȣ����ֻ�ܴ洢����
			int len = min(2, index - i);
			for (int j = 0; j < len; j++) {
				nums[k+j] = nums[i];
			}
			 // i�͵���һ�β��ظ� ������
			i = index;
			// ά���µ����飬ָ����һ��λ��
			k = k + len;
		}
		return k;
	}
};