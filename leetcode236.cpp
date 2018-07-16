/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {} 
* };
*/


/*
   ²¢¼¯
*/
class Solution {
public:
	TreeNode* res;
	pair<bool, bool> dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL)return make_pair(false, false);
		auto l = dfs(root->left, p, q);
		auto r = dfs(root->right, p, q);
		r.first |= l.first|(l==p);
		r.second |= l.second(r==q);
		if (r.first&&r.second&&ret == NULL)ret = root;
		return r;
	}
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		res = NULL;
		dfs(root, p, q);
		return res;
	}
};