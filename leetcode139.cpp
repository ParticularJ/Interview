/*
	思路：对字符串进行拆分，分别对左右进行判断，并且使用内存记录左边的正确与否

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
	// 使用mem_记录之前的判断结果。比如说判断”“， "l" , "le",...
	unordered_map<string, bool> mem_;
	bool wordBreak(string s, vector<string>& wordDict) {
		//将字符串统一记录在set里，方便后续访问，统计
		unordered_set<string> dict(wordDict.cbegin(), wordDict.cend());
		return wordBreak(s, dict);
	}

	bool wordBreak(string& s, unordered_set<string>& dict) {
		//返回之前统计的ture or false
		if (mem_.count(s))return mem_[s];
		// 如果在字典中返回true
		if (dict.count(s))return mem_[s] = true;
		for (int i = 1; i < s.size(); i++) {
			string l = s.substr(0, i);
			string r = s.substr(i);
			//记录左边，判断右边
			if (dict.count(r) && wordBreak(l, dict)) {
				return mem_[s] = true;
			}
		}
		return mem_[s] = false;
	}
};