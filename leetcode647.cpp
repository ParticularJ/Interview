/*
枚举所有的可能行，求解。
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
从中间向两边扩展
*/

class Solution {

	int countSubstrings(string s) {
		int size = s.size();
		if (size == 0)return 0;
		int res = 0;
		for (int i = 0; i < size; i++) {
			int l = i, r = i;

			// 计算对称的回文数,例如“aaa"
			// 计算的是 a, a, aaa
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

			//计算间隔
			// 比如 aa
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