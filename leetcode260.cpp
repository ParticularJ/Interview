/*
异或的作用：
用0 和一组重复出现的数字异或，最终结果为，只出现一次的数
0^N1^N2^N2^N4^N3^N4^N3
= N1
*/

class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int n = 0;
		for (auto i : nums)
			n ^= i;
		// 结果便是 A^B,
		// 3 ^ 5
		// 一个数与负数的异或就是他们不同的那一位
		// 0011 0101  异或后 0110
		// 0110 和负的他与，即为 0010即为3和5不同的一位
		// 区分开A和B
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