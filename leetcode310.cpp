/*
构建图，然后删除度为1的点，重新构建图，再次删除与前一步度为1的点相连的点度
当最后度为0或者1时即为所求的点。

例子  0
      |
	  1
	 / \
    2   3   ,构建图 0，2，3的度为1， 1的为3，删除为度为1的；因为删除的与1相连，再次构建后删除0，2，3的度
	         得到1的度为0.


  0  1  2
  \  |  /
     3
	 |     ,构建图，删除0，1，2，5后新图的剩下3， 4，再删除与之相连，的3和4的度为1即为所求值
	 4
	 |
	 5
*/


class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
		vecotor<int> res;
		if (n == 0)return res;
		if (n == 1) {
			res.push_back(0);
			return res;
		}

		//构建图
		vector<vector<int> > graph(n, vector<int>());
		vector<int> degree(n, 0);
		
		// 构建图和度
		for (auto i : edges) {
			graph[i.first].push_back(i.second);
			graph[i.second].push_back(i.first);
			degree[i.first]++;
			degree[i.second]++;
		}
		//删除度为1的
		int cnt = n;
		while (cnt > 2) {
			// 记录度为1的值
			vector<int> record;
			for(int j=0;j<n;j++)
				for (auto i : graph[j]) {
					if (degree[i] == 1) {
						record.push_back(i);
						degree[i] = -1;
						cnt--;
					}
				}
			// 找到上一层，减去对应的度
			for (int i = 0; i < record.size(); i++) {
				for (auto i : graph[record[i]]) {
					degree[i]--;
				}
			}
		}

		for (int i = 0; i < degree.size(); i++) {
			if (degree[i] == 0 || degree[i] == 1)
				res.push_back(i);
		}
		return res;
	}
};