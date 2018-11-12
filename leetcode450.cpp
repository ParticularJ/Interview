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
	TreeNode* findmin(TreeNode* root) {
		if (root->left == NULL)
			return root;
		return findmin(root->left);
	}

	TreeNode* removemin(TreeNode* root) {
		if (root == NULL)
			return root;
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			delete root;
			return temp;

		}
		root->left = removemin(root->left);
		return root;
	}

	TreeNode* isRoot(TreeNode* root, int key) {
		if (root == NULL)
			return NULL;
		if (root->val == key) {
			if (root->right == NULL) {
				TreeNode*leftNode = root->left;
				delete root;
				return leftNode;
			}
			else if (root->left == NULL) {
				TreeNode* rightNode = root->right;
				delete root;
				return rightNode;
			}
			else {
				// 注意，有可能removemin 可能刚好删除successor所以我们要新建一个successor
				// 满足二叉搜索树的性质，右子树最小的值刚好符合条件。
				TreeNode* successor = new TreeNode(findmin(root->right)->val);
				successor->left = root->left;
				successor->right = removemin(root->right);
				delete root;
				return successor;
			}

		}
		else {
			// 大于key,递归左子树
			if (root->val > key) {
				root->left = isRoot(root->left, key);
				return root;
			}
			// 小于key，递归右子树
			else if (root->val < key) {
				root->right = isRoot(root->right, key);
				return root;
			}
		}
	}
	TreeNode* deleteNode(TreeNode* root, int key) {
		if (root == NULL)
			return NULL;
		return isRoot(root, key);
	}
};