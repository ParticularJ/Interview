/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
	// 统计当前值，和当前层的个数
	vector<pair<long long, int> > res;
	void dfs(TreeNode* root, int depth) {

		if (root->left) {
			dfs(root->left, depth + 1);
		}
		while (depth >= res.size())
			res.push_back(make_pair(0, 0));
		res[depth].first += double(root->val);
		res[depth].second += 1;

		if (root->right) {
			dfs(root->right, depth + 1);
		}
	}
	vector<double> averageOfLevels(TreeNode* root) {
		dfs(root, 0);
		vector<double> res1;
		for (int i = 0; i<res.size(); i++) {
			// cout<< res[i].first;
			res1.push_back(res[i].first*1.0 / res[i].second);
		}
		return res1;
	}
};