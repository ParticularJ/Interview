#include<iostream>
#include<stack>
#include<string>

using namespace std;

/*
	两个函数：
	atoi()字符串转为int
	c_str()将字符串转为char[]格式
	出栈与入栈的顺序
*/

class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		int size = tokens.size();
		int res = 0;
		stack<int> st;
		if (size == 0)return res;
		for (auto i:tokens) {
			if (i == "+" || i == "-" || i == "*" || i == "/") {
				int top = st.top(); st.pop();
				int bottom = st.top(); st.pop();
				int ans = 0;
				if (i == "+")ans = top + bottom;
				if (i == "-")ans = bottom - top;
				if (i == "*")ans = top * bottom;
				if (i == "/")ans = bottom / top;
				st.push(ans);
			}
			else {
				int num = atoi(i.c_str());
				st.push(num);
			}
		}
		return st.top();
	}
};