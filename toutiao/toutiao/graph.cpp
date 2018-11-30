#include<iostream>
#include<istream>
#include<vector>
#include<string>
#include<sstream>
#include<stack>
using namespace std;

vector<vector<int> > G;
vector<bool> visited;
// 记录路径
vector<int> from;

void dfs(int i) {
	// cout << "etest" << endl;
	visited[i] = true;
	for (auto e : G[i]) {
	//	cout << e <<endl;
		if (!visited[e])
			from[e] = i;
			dfs(e);
	}
}

vector<int> findPath(int n) {
	vector<int> res;
	stack<int> path;
	while (from[n] != -1) {
		path.push(from[n]);
		n = from[n];
	}
	while (path.size()) {
		res.push_back(path.top());
		path.pop();
	}
	return res;
}


int main() {
	// 共计人数， 1开始
	int n;
	cin >> n;
	vector<vector<int> > graph(n,vector<int>());
	//cout << graph.size();
	G = graph;
	from = vector<int>(n, -1);
	//认识的人
	string line;

	int count = 0;
	int a;
	// 读取换行
	getline(cin, line);
	for(int i=0;i<n;i++){
		getline(cin, line);
		stringstream mystr;
		mystr.str(line);
		while (1) {
			mystr >> a;
			if (mystr.fail())break;
		//	cout << i;
			if(a!=0)
				G[i].push_back(a-1);
		}
	}
	//for (auto i : G){
	//	for (auto j : i)
	//		cout << j;
	//	cout << endl;
	//}
	visited = vector<bool>(n, false);
	for (int i = 0; i < G.size();i++) {
		for (auto j : G[i]) {
			if (!visited[j]) {
				//cout<<i;
				dfs(j);
				count++;
			}
		}
		cout << count << endl;
	}
	cout<< count;





	return 0;

}