class Solution {
public:
	string simplifyPath(string path) {
		int size = path.size();
		stack<string> st;
		for (int i = 0; i<size;) {
			// �Թ���һ��'/'


			i += 1;
			if (i == size)break;
			// �ų� "///"���
			if (path[i] == '/')continue;
			int j = i;
			// ȡ�� ����"/"֮���ֵ
			while (j + 1<size && path[j + 1] != '/')j++;

			string  temp = path.substr(i, j - i + 1);

			// '.'�Ļ�������
			if (temp == ".") {
				continue;
			}
			else {
				//".."�Ļ������st��Ϊ�գ���ջһ��
				if (temp == "..") {
					if (st.size() > 0)
						st.pop();
				}
				else
					st.push(temp);
			}
			// ����һ����/��λ��
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