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
		// �ж��Ƿ�ΪҶ��
		bool is_leave = (root->left == NULL) && (root->right == NULL);
		// �ǵĻ�����1
		if (is_leave)return 1;
		
		// �����������������Ƚ��ҳ���С��
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