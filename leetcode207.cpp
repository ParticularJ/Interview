#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<map>
using namespace std;

/*
	图的遍历，分为DFS 和 BFS 。 
	DFS 使用一个stack维护
	BFS 使用一个queue维护
	拓扑排序：只能有前向的一种排序，不能有回路。
	要记录入度，即一共有几个点流入改顶点，那么入度就为几。
*/

class Solution {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		// 由于担心prerequisites一个特别大，一个贴别小，我们可以先对其重新编号
		map<int, int> rename;
		vector<int> deg(1, 0);
		vector<vector<int> > edge(1, vector<int>());
		int index = 0;
		for (auto i : prerequisites) {
			int first = i.first;
			if (rename[first] == 0) {
				rename[first] = ++index;
				// 创建邻接表
				edge.push_back(vector<int>());
				// 因为没有出现过，所以他的入度必为0
				deg.push_back(0);
			}
			int second = i.second;
			if (rename[second] == 0) {
				rename[second] = ++index;
				edge.push_back(vector<int>());
				deg.push_back(0);
			}
			// 因为后面是前面的先题条件，所以将前面的压入后面
			// 即拓扑排序只能有前向的不能后向，所以是second->first
			edge[rename[second]].push_back(rename[first]);
			// 因此，first的入度加1
			deg[rename[first]] += 1;
		}

		// BFS需要队列维护, 
		queue<int> que;
		for (int i = 1; i <= index; i++) {
			if (deg[i] == 0) {
				que.push(i);
			}
		}

		for (; que.size() > 0; que.pop()) {
			int front = que.front();
			// 去遍历与该顶点相连的顶点
			for (auto i : edge[front]) {
				deg[i] -= 1;
				if (deg[i] == 0) {
					que.push(i);
				}
			}
		}
		for (int i = 1; i <= index; i++) {
			if (deg[i] != 0) {
				return false;
			}
		}
		return true;
	}
};