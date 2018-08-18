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
���ζ�̬�滮�������������һ��ȡ����ȥ���ҽڵ�
һ����ȡ���ҽڵ㣬��ȡ�����жϴ�С

*/
class Solution {
public:
	// pair �洢ȡ���Ͳ�ȡ��. first ��ȡ�� second ȡ
	pair<int, int> dfs(TreeNode* root) {
		if (root == NULL)return make_pair(0, 0);
		auto left = dfs(root->left);
		auto right = dfs(root->right);
		pair<int, int> res = make_pair(0, 0);
		//ȡ��
		res.second = root->val + left.first + right.first;
		res.first = max(left.first, left.second) + max(right.first, right.second);
		return res;
	}

	int rob(TreeNode* root) {
		if (root == NULL)return 0��
		auto temp = dfs(root);
		return max(temp.first, temp.second);
	}
};