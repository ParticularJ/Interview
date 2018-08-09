/*
struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	int val;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
*/

/*

取得TreeNode 为 root, 断开左右结点后，dfs左右
将根节点接在flat右边。


*/

class Solution {
public:
	TreeNode* flat;
	void dfs(TreeNode* temp) {
		if (temp == NULL)return;
		TreeNode *left = temp->left, *right = temp->right;
		//断开，否则会乱
		temp->left = NULL, temp->right = NULL;
		flat->right = temp;
		flat = temp;
		dfs(left);
		dfs(right);
	}


	void flatten(TreeNode* root) {
		if (root == NULL)return;
		// 通过flat记录根节点
		flat = root;
		TreeNode* l = flat->left, *r = flat->right;
		//断开，否则会乱
		root->left = NULL, root->right = NULL;
		dfs(l);
		dfs(r);
	}
};