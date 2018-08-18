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
树形动态规划，分两种情况，一种取根不去左右节点
一种是取左右节点，不取根，判断大小

*/
class Solution {
public:
	// pair 存储取根和不取根. first 不取， second 取
	pair<int, int> dfs(TreeNode* root) {
		if (root == NULL)return make_pair(0, 0);
		auto left = dfs(root->left);
		auto right = dfs(root->right);
		pair<int, int> res = make_pair(0, 0);
		//取根
		res.second = root->val + left.first + right.first;
		res.first = max(left.first, left.second) + max(right.first, right.second);
		return res;
	}

	int rob(TreeNode* root) {
		if (root == NULL)return 0；
		auto temp = dfs(root);
		return max(temp.first, temp.second);
	}
};