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
	vector<vector<int> > res;
	void dfs(TreeNode* root, int sum, int target, vector<int>& temp) {

		if (root->left == NULL && root->right == NULL) {
			temp.push_back(root->val);
			if (target == sum + root->val) {
				res.push_back(temp);
			}
			temp.pop_back();
		}
		else {
			temp.push_back(root->val);
			if (root->left) {
				dfs(root->left, sum + root->val, target, temp);
			}
			if (root->right) {
				dfs(root->right, sum + root->val, target, temp);
			}
			temp.pop_back();
		}
	}


	vector<vector<int>> pathSum(TreeNode* root, int sum) {

		if (root == NULL)
			return res;
		vector<int> temp;
		dfs(root, 0, sum, temp);
		return res;

	}
};