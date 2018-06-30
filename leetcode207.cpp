#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<map>
using namespace std;

/*
	ͼ�ı�������ΪDFS �� BFS �� 
	DFS ʹ��һ��stackά��
	BFS ʹ��һ��queueά��
	��������ֻ����ǰ���һ�����򣬲����л�·��
	Ҫ��¼��ȣ���һ���м���������Ķ��㣬��ô��Ⱦ�Ϊ����
*/

class Solution {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		// ���ڵ���prerequisitesһ���ر��һ������С�����ǿ����ȶ������±��
		map<int, int> rename;
		vector<int> deg(1, 0);
		vector<vector<int> > edge(1, vector<int>());
		int index = 0;
		for (auto i : prerequisites) {
			int first = i.first;
			if (rename[first] == 0) {
				rename[first] = ++index;
				// �����ڽӱ�
				edge.push_back(vector<int>());
				// ��Ϊû�г��ֹ�������������ȱ�Ϊ0
				deg.push_back(0);
			}
			int second = i.second;
			if (rename[second] == 0) {
				rename[second] = ++index;
				edge.push_back(vector<int>());
				deg.push_back(0);
			}
			// ��Ϊ������ǰ����������������Խ�ǰ���ѹ�����
			// ����������ֻ����ǰ��Ĳ��ܺ���������second->first
			edge[rename[second]].push_back(rename[first]);
			// ��ˣ�first����ȼ�1
			deg[rename[first]] += 1;
		}

		// BFS��Ҫ����ά��, 
		queue<int> que;
		for (int i = 1; i <= index; i++) {
			if (deg[i] == 0) {
				que.push(i);
			}
		}

		for (; que.size() > 0; que.pop()) {
			int front = que.front();
			// ȥ������ö��������Ķ���
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