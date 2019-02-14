class Solution {
public:
	string simplifyPath(string path) {
		int size = path.size();
		stack<string> st;
		for (int i = 0; i<size;) {
			// 略过第一个'/'


			i += 1;
			if (i == size)break;
			// 排除 "///"情况
			if (path[i] == '/')continue;
			int j = i;
			// 取出 两个"/"之间的值
			while (j + 1<size && path[j + 1] != '/')j++;

			string  temp = path.substr(i, j - i + 1);

			// '.'的话，继续
			if (temp == ".") {
				continue;
			}
			else {
				//".."的话，如果st不为空，出栈一个
				if (temp == "..") {
					if (st.size() > 0)
						st.pop();
				}
				else
					st.push(temp);
			}
			// 到下一个’/‘位置
			i = j + 1;
		}
		if (st.size() == 0)return "/";
		vector<string> temp;
		for (; st.size();) {
			temp.push_back(st.top());
			st.pop();
		}
		string res;
		for (int i = temp.size() - 1; i >= 0; i--)
			res += "/" + temp[i];
		return res;


	}
};