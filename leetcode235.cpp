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
		// p,q��Ϊnull,����null
		if (p == NULL || q == NULL)
			return NULL;
		if (root == NULL)
			return NULL;
		// �ɶ��������ʿ�֪����С�ڸ��ڵ㣬�����ң�����������
		if (p->val < root->val && q->val < root->val)
			return lowestCommonAncestor(root->left, p, q);
		if (p->val > root->val && q->val > root->val)
			return lowestCommonAncestor(root->right, p, q);
		// һ��һ�ҷ��ظ�
		return root;
	}
};