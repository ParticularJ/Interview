#include<vector>
#include<queue>
using namespace std;


// 邻接矩阵实现图
class DenseGraph {
private:
	// 顶点
	int n;
	// 边
	int m;
	// 有无向
	bool directed;
	// 邻接矩阵
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


// 邻接表实现

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

		// 自环边
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



// 简单无权图最短路径

int shortPath(int s, int size_of_graph, vector<vector<int>>& graph) {
	// 遍历点，
	vector<int> visited(size_of_graph, false);
	queue<int> q;
	// 记录距离
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




