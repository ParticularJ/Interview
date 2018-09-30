/*
�ȴӸ����ͷţ����ݵ�һ���������򣬵�һ����ȣ����ݵڶ�������
����second��λ��
100 0��100 1

*/
class Solution {
public:
	static bool cmp(pair<int, int>& a, pair<int, int>& b) {
		if (a.first != b.first)return a.first > b.first;
		else
			return a.second < b.second;
	}
	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
		int size = people.size();
		vector<pair<int, int> > res(size);
		int cnt = 0;
		sort(people.begin(), people.end(), cmp);
		for (int i = 0; i < size; i++) {
			if (people[i].second < cnt) {
				res.insert(res.begin() + people[i].second, people[i]);
				cnt += 1;
			}
			else {
				res[i] = people[i];
				cnt += 1;
			}
		}
		while (res.size()>size)res.erase(res.end());
		return res;
	}
};

class Solution {
public:
	static bool cmp(pair<int, int> &a, pair<int, int>& b){
		if (a.first != b.first)return a.first > b.first;
		else
			return a.second < b.second;
	}
	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
		int size = people.size();
		vector<pair<int, int> > res(size);
		int cnt = 0; 
		sort(people.begin(), people.end(), cmp);
		for (auto i:people) {
			if (i.second < cnt) {
				for (int j = cnt; j > i.second; j--)
					res[j] = res[j - 1];
			}
			res[i.second] = i;
			cnt += 1;
		}
		return res;
	}
};