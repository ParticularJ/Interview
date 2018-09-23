/*
�������ã�
��0 ��һ���ظ����ֵ�����������ս��Ϊ��ֻ����һ�ε���
0^N1^N2^N2^N4^N3^N4^N3
= N1
*/

class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int n = 0;
		for (auto i : nums)
			n ^= i;
		// ������� A^B,
		// 3 ^ 5
		// һ�����븺�������������ǲ�ͬ����һλ
		// 0011 0101  ���� 0110
		// 0110 �͸������룬��Ϊ 0010��Ϊ3��5��ͬ��һλ
		// ���ֿ�A��B
		int m = n&(-n);
		vector<int> res(2, 0);
		for (auto i : nums) {
			
			if ((i&m) == 0)
				res[0] ^= i;
			else
				res[1] ^= i;
		}
		return res;
	}
};