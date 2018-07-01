class Solution {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
		int index = 0;
		map<int, int> rename;
		map<int, int> rev_rename;
		vector<int> deg;
		vector<vector<int> > edge;
		for (auto i : prerequisites) {
			int first = i.first;
			if (rename[first] == 0) {
				rename[first] = ++index;
				rev_rename[index] = first;
				edge[rename[first]].push_back(vector<int>());
				deg.push_back(0);
			}
			int second = i.second;
			if (rename[second] == 0) {
				rename[second] = ++index;
				rev_rename[index] = second
				edge[rename[second]].push_back(vector<int>());
				deg.push_back(0);
			}
			edge[rename[second]].push_back(rename[first]);
			deg[rename[first]] += 1£»
		}
		queue<int> que;
		vector<int> res;
		for (int i = 1; i <= index; i++) {
			if (deg[i] == 0) {
				res.push_back(rev_rename[i]);
				que.push(i);
			}
		}
		for (; que.size() > 0; que.pop()) {
			int front = que.front();
			if (deg[front]) {
				deg[front] -= 1;
				if (deg[front] == 0) {
					res.push_back(rev_rename[front]);
					que.push(front);
				}
			}
		}
		for (int i = 0; i < numCourses; i++) {
			if (rename[i] == 0) {
				res.push_back(i);
			}
		}
		return res;
	}
};