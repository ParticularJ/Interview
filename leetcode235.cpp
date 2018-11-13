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
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		// p,q都为null,返回null
		if (p == NULL || q == NULL)
			return NULL;
		if (root == NULL)
			return NULL;
		// 由二叉树性质可知，都小于根节点，往左找，否则往右找
		if (p->val < root->val && q->val < root->val)
			return lowestCommonAncestor(root->left, p, q);
		if (p->val > root->val && q->val > root->val)
			return lowestCommonAncestor(root->right, p, q);
		// 一左一右返回根
		return root;
	}
};