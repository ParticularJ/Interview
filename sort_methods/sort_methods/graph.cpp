#include<vector>
#include<queue>
using namespace std;


// �ڽӾ���ʵ��ͼ
class DenseGraph {
private:
	// ����
	int n;
	// ��
	int m;
	// ������
	bool directed;
	// �ڽӾ���
	vector<vector<int> > g;
public:
	DenseGraph(int n, bool directed) {
		this->n = n;
		this->directed = directed;
		this->m = 0;
		for (int i = 0; i < n; i++) {
			g.push_back(vector<int>(n, false));
		}
	}
	~DenseGraph() {
	
	}

	int V() { return n; }
	int E() { return m; }

	void addEdge(int i, int j) {
		if (hasEdge(i, j))
			return;

		g[i][j] = true;
		if (!directed)
			g[j][i] = true;
		m++;
	}

	bool hasEdge(int i, int j) {
		return g[i][j];
	}

};


// �ڽӱ�ʵ��

class SparseGraph {
private:
	int n, m;
	bool directed;
	vector<vector<int> > g;
public:
	SparseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0; 
		this->directed = directed;
		for (int i = 0; i < n; i++) {
			g.push_back(vector<int>());
		}
	}

	~SparseGraph() {

	}

	int V() { return n; };
	int E() { return m; };

	void addEdge(int i, int j) {
		
		
		g[i].push_back(j);

		// �Ի���
		if (i!=j && !directed) {
			g[j].push_back[i];
		}
		m++;
	}

	bool hasEdge(int v, int w) {
		for (int i = 0; i < g[v].size(); i++) {
			if (w == g[v][i])
				return true;
		}
		return false;
	}
};



// ����Ȩͼ���·��

int shortPath(int s, int size_of_graph, vector<vector<int>>& graph) {
	// �����㣬
	vector<int> visited(size_of_graph, false);
	queue<int> q;
	// ��¼����
	vector<int> dis;
	int count = 1;
	q.push(s);
	visited[s] = true;
	dis[s] = 0;
	while (!q.empty()) {
		int top = q.front();
		q.pop();
		for (auto i : graph[top]) {
			if (!visited[i]) {
				visited[i] = true;
				dis[i] = dis[top] + 1;
				q.push(i);
			}
		}
	}
	return dis[s];
}




