/*
����ͼ��Ȼ��ɾ����Ϊ1�ĵ㣬���¹���ͼ���ٴ�ɾ����ǰһ����Ϊ1�ĵ������ĵ��
������Ϊ0����1ʱ��Ϊ����ĵ㡣

����  0
      |
	  1
	 / \
    2   3   ,����ͼ 0��2��3�Ķ�Ϊ1�� 1��Ϊ3��ɾ��Ϊ��Ϊ1�ģ���Ϊɾ������1�������ٴι�����ɾ��0��2��3�Ķ�
	         �õ�1�Ķ�Ϊ0.


  0  1  2
  \  |  /
     3
	 |     ,����ͼ��ɾ��0��1��2��5����ͼ��ʣ��3�� 4����ɾ����֮��������3��4�Ķ�Ϊ1��Ϊ����ֵ
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

		//����ͼ
		vector<vector<int> > graph(n, vector<int>());
		vector<int> degree(n, 0);
		
		// ����ͼ�Ͷ�
		for (auto i : edges) {
			graph[i.first].push_back(i.second);
			graph[i.second].push_back(i.first);
			degree[i.first]++;
			degree[i.second]++;
		}
		//ɾ����Ϊ1��
		int cnt = n;
		while (cnt > 2) {
			// ��¼��Ϊ1��ֵ
			vector<int> record;
			for(int j=0;j<n;j++)
				for (auto i : graph[j]) {
					if (degree[i] == 1) {
						record.push_back(i);
						degree[i] = -1;
						cnt--;
					}
				}
			// �ҵ���һ�㣬��ȥ��Ӧ�Ķ�
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