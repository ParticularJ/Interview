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
	int countLeft(TreeNode* root) {
		if (root == NULL)
			return 0;
		return 1 + countLeft(root->left);
	}

	int countRight(TreeNode* root) {
		if (root == NULL)
			return 0;
		return 1 + countRight(root->right);
	}

	int countNodes(TreeNode* root) {
		int res = 0;
		if (root == NULL)
			return 0;
		//统计左子树的左子树高度
		int leftLeft = countLeft(root->left);
		// 统计右子树高度
		int leftRight = countRight(root->left);
		if (leftLeft == leftRight)
			return 1 + (1 << leftLeft - 1) + countNodes(root->right);
		if (leftLeft = leftRight + 1)
			return 1 + (1 << leftRight - 1) + countNodes(root->left);



	}
};