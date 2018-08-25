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
	vector<vector<int> > res;
	void dfs(TreeNode* root, int depth) {
		if (root->left) {
			dfs(root->left, depth + 1);
		}

		// 根据大小，给res添加一维数组
		while (depth >= res.size()) 
			res.push_back(vector<int>());
		res[depth].push_back(root->val);
		if (root->right) {
			dfs(root->right, depth + 1);
		}
	}

	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		if (root == NULL)return res;
		dfs(root, 0);
		reverse(res.begin(), res.end());
		return res;
	}
};