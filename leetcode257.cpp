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
	vector<string> res;
	void dfs(TreeNode* root, string v) {
		if (v == "")
			v += to_string(root->val);
		else
			v += "->" + to_string(root->val);
		if (root->right == NULL && root->left == NULL)
			res.push_back(v);
		if (root->left)
			dfs(root->left, v);
		if (root->right)
			dfs(root->right, v);
	}
	vector<string> binaryTreePaths(TreeNode* root) {
		if (root == NULL)return res;
		dfs(root, "");
		return res;
	}
};