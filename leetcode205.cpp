/*
ģ��ӳ��
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
			// ���aû��ӳ���
			if (!mymapa[a]) {
				// b�Ѿ�ӳ����
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