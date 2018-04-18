#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
主要思路：字符串的滑动窗口，我们分别统计s,p中字母出现的次数
因为都是小写字符，所以使用[char - 'a']可以很方便的统计不同字符出现的次数，
比如说"abd",对应的便是[1,1,0,1,...(length)].
直接使用vector比较，相同元素相同位置则返回true，
接下来的思想是滑动窗口的思想，
也就是s每向前移动一步，统计出新的字符的情况，（减去之前的，加上新增的）
再通过和统计的p进行比较，返回位置。
*/




class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		vector<int> res;
		vector<int> countP(26);
		vector<int> countS(26);
		int lenp = p.length(), lens = s.length();
		if (!lenp || !lens || lenp > lens)return res;
		for (int i = 0; i < lenp; i++) {
			countP[p[i] - 'a']++;
			countS[s[i] - 'a']++;
		}
		if (countP == countS) res.push_back(0);
		for (int i = 1; i < lens; i++) {
			if (i + lenp > lens)break;
			countS[s[i - 1] - 'a']--;
			countS[s[i + lenp - 1] - 'a']++;
			if (countP == countS) res.push_back(i);
		}
		return res;
	}
};



int main() {
	Solution find;
	string a = "cbaebabacd";
	string b = "abc";
	vector<int> c;
	c = find.findAnagrams(a, b);
	for (auto s : c) {
		cout << s;
	}
	
	return 0;

}