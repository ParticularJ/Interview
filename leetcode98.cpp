//方案一：中序遍历，保存每一个值，从而判断其是否为正确的二分搜索树

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
	vector<int> res;
	void inorder(TreeNode* root) {
		if (root == NULL)
			return;
		inorder(root->left);
		res.push_back(root->val);
		inorder(root->right);
	}


	bool isValidBST(TreeNode* root) {
		if (root == NULL)
			return true;
		inorder(root);
		for (int i = 1; i<res.size(); i++) {
			if (res[i - 1] >= res[i])
				return false;
		}
		return true;

	}
};



// 方案二：比较左子树的最大值是否小于根结点以及右子树的最小值是否大于根节点

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
	bool flag;

	pair<int, int> dfs(TreeNode* root) {
		int mini = (1ll << 31)-1;
		int maxi = -(1ll << 31);
		
		if (root->left != NULL) {
			pair<int, int> l = dfs(root->left);
			if (l.second >= root->val)
				flag = false;
			mini = l.first;
		}
		if (root->right != NULL) {
			pair<int, int> r = dfs(root->right);
			if (r.first <= root->val)
				flag = false;
			maxi = r.second;
		}
		mini = min(mini, root->val);
		maxi = max(maxi, root->val);
		return make_pair(mini, maxi);
		
	}



	bool isValidBST(TreeNode* root) {
		if (root == NULL)
			return true;
		flag = true;
		dfs(root);
		return flag;

	}
};







