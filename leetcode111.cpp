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
	int dfs(TreeNode* root) {
		// 判断是否为叶子
		bool is_leave = (root->left == NULL) && (root->right == NULL);
		// 是的话返回1
		if (is_leave)return 1;
		
		// 和左子树和右子树比较找出最小的
		int res = INT_MAX;
		if (root->left) {
			res = min(res, dfs(root->left));
		}
		if (root->right) {
			res = min(res, dfs(root->right));
		}
		res += 1;
		return res;
	}

	int minDepth(TreeNode* root) {
		return dfs(root);
	}
};