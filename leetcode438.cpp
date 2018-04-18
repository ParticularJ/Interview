#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
��Ҫ˼·���ַ����Ļ������ڣ����Ƿֱ�ͳ��s,p����ĸ���ֵĴ���
��Ϊ����Сд�ַ�������ʹ��[char - 'a']���Ժܷ����ͳ�Ʋ�ͬ�ַ����ֵĴ�����
����˵"abd",��Ӧ�ı���[1,1,0,1,...(length)].
ֱ��ʹ��vector�Ƚϣ���ͬԪ����ͬλ���򷵻�true��
��������˼���ǻ������ڵ�˼�룬
Ҳ����sÿ��ǰ�ƶ�һ����ͳ�Ƴ��µ��ַ������������ȥ֮ǰ�ģ����������ģ�
��ͨ����ͳ�Ƶ�p���бȽϣ�����λ�á�
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