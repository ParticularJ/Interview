/*
	˼·�����ַ������в�֣��ֱ�����ҽ����жϣ�����ʹ���ڴ��¼��ߵ���ȷ���

	leetcode  dict:"leet", "code"

	"" && "leetcode"
	"l" && "eetcode"
	"le" && "etcode"
	"lee" && "tcode"
	"leet" && "code" 
	....
	"leetcod" && "e"
*/


class Solution {
public:
	// ʹ��mem_��¼֮ǰ���жϽ��������˵�жϡ����� "l" , "le",...
	unordered_map<string, bool> mem_;
	bool wordBreak(string s, vector<string>& wordDict) {
		//���ַ���ͳһ��¼��set�����������ʣ�ͳ��
		unordered_set<string> dict(wordDict.cbegin(), wordDict.cend());
		return wordBreak(s, dict);
	}

	bool wordBreak(string& s, unordered_set<string>& dict) {
		//����֮ǰͳ�Ƶ�ture or false
		if (mem_.count(s))return mem_[s];
		// ������ֵ��з���true
		if (dict.count(s))return mem_[s] = true;
		for (int i = 1; i < s.size(); i++) {
			string l = s.substr(0, i);
			string r = s.substr(i);
			//��¼��ߣ��ж��ұ�
			if (dict.count(r) && wordBreak(l, dict)) {
				return mem_[s] = true;
			}
		}
		return mem_[s] = false;
	}
};