class Solution {
public:
	vector<string> split(string& str) {
		vector<string> temp;
		// �ָ��ַ�
		for (int i = 0, index = 0; i <= str.size(); ) {
			if (str[i] == ' ' || i == str.size()) {
				string s = str.substr(index, i - index);
				temp.push_back(s);
				i = i + 1;
				index = i;
			}
			else
				i++;
		}
		return temp;
	}
	bool wordPattern(string pattern, string str) {
		//���Ƚ�str �е��ַ������зָ�
		vector<string> S = split(str);
		// ͨ��ӳ���ϵ���ж�
		unordered_map<string, char> s2c;
		unordered_map<char, string> c2s;

		if (pattern.size() != S.size())
			return false;
		for (int i = 0; i < S.size(); i++) {
			char p = pattern[i];
			string s = S[i];
			if (c2s.find(p) == c2s.end()) {
				if (s2c.find(s) == s2c.end()) {
					c2s[p] = s;
					s2c[s] = p;
				}
				else
					if (s2c[s] != p)
						return false;
			}
			else
				if (c2s[p] != s)
					return false;
		}
		return true;
	}
};