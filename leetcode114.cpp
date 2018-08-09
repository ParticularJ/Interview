/*
struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	int val;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
*/

/*

ȡ��TreeNode Ϊ root, �Ͽ����ҽ���dfs����
�����ڵ����flat�ұߡ�


*/

class Solution {
public:
	TreeNode* flat;
	void dfs(TreeNode* temp) {
		if (temp == NULL)return;
		TreeNode *left = temp->left, *right = temp->right;
		//�Ͽ����������
		temp->left = NULL, temp->right = NULL;
		flat->right = temp;
		flat = temp;
		dfs(left);
		dfs(right);
	}


	void flatten(TreeNode* root) {
		if (root == NULL)return;
		// ͨ��flat��¼���ڵ�
		flat = root;
		TreeNode* l = flat->left, *r = flat->right;
		//�Ͽ����������
		root->left = NULL, root->right = NULL;
		dfs(l);
		dfs(r);
	}
};