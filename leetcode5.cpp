class Solution {
public:
	string longestPalindrome(string s) {
		string res = "";
		int size = s.size();
		if (size < 2)return res;
		// ��¼����ȣ��Լ���˵�
		int left, right, max_len = 1, max_left;
		// �ж�һ�뼴��
		for (int start = 0; start < size && size - start > max_len/2; ) {
			left = right = start;
			while (right < size - 1 && s[right + 1] == s[right])
				right++;
			start = right + 1;
			while (right < size - 1 && left > 0 && s[right + 1] == s[left - 1]) {
				right++;
				left--;
			}
			if (max_len < right - left + 1) {
				max_left = left;
				max_len = right - left + 1;
			}
		}
		return s.substr(max_left, max_len);
	}
};