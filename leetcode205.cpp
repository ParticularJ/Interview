/*
模拟映射
*/
class Solution {
public:
	bool isIsomorphic(string s, string t) {
		int size = s.size();
		unordered_map<char, char> mymapa;
		unordered_map<char, char> mymapb;
		for (int i = 0; i < size; i++) {
			char a = s[i];
			char b = t[i];
			// 如果a没有映射过
			if (!mymapa[a]) {
				// b已经映射了
				mymapa[a] = b;
				if (!mymapb[b])
					mymapb[b] = a;
				else
					if (mymapb[b] != a)
						return false;

			}
			else {
				if (mymapa[a] != b)
					return false;
			}

		}
		return true;
	}
};