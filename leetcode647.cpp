/*
ö�����еĿ����У���⡣
*/


class Solution {
public:
	bool isPalindromic(string &S) {
		int size = S.size();
		int l = 0, r = size - 1;
		while (l < r && S[l++] == S[r--])return 1;
		return 0;
	}


	int countSubstrings(string s) {
		int size = s.size();
		if (size == 0)return 0;
		int res = 0;
		for (int i = 0; i < size; i++)
			for (int j = i; j < size; j++)
				res+=isPalindromic(s.substr(i, j-i+1));
		return res;
	}
};


/*
���м���������չ
*/

class Solution {

	int countSubstrings(string s) {
		int size = s.size();
		if (size == 0)return 0;
		int res = 0;
		for (int i = 0; i < size; i++) {
			int l = i, r = i;

			// ����ԳƵĻ�����,���硰aaa"
			// ������� a, a, aaa
			while (l - 1 >= 0 && r + 1 < size) {
				if (s[l - 1] == s[r + 1]) {
					l--;
					r++;
				}
				else {
					break;
				}
			}
			res += r - i + 1;

			//������
			// ���� aa
			l = i + 1;
			r = i;
			while (l - 1 >= 0 && r + 1 < size) {
				if (s[l - 1] == s[r + 1]) {
					l--;
					r++;
				}
				else
					break;
			}
			res += r - i;
		}
			
		return res;
	}
};