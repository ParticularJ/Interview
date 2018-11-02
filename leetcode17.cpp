/*
Given a string containing digits from 2 - 9 inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters(just like on the telephone buttons) is given below.Note that 1 does not map to any letters.



Example:

Input: "23"
Output : ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
*/

class Solution {
public:
	string letter = { "ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf" };

	vector<string> res;
	void dfs(string digits, int index, string & s) {
		if (index == digits.size()) {
			res.push_back(s);
			return;
		}

		char c = digits[index];
		string temp = letter[c - '2'];
		for (int i = 0; i < temp.size(); i++) {
			dfs(digits, index + 1, s + temp[i]);
		}
		return;
	
	}

	vector<string> letterCombinations(string digits) {
		if (digits == "")
			return res;
		dfs(digits, 0, "");
		return res;
	}
};