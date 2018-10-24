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

	void dfs(TreeNode*root, vector<int> & temp) {
		if (root->left == NULL && root->right == NULL) {
			temp.push_back(root->val);
			res.push_back(temp);
			temp.pop_back();
		}
		else {
			temp.push_back(root->val);
			if (root->left)
				dfs(root->left, temp);
			if (root->right)
				dfs(root->right, temp);
			temp.pop_back();
		}

	}

	int sumNumbers(TreeNode* root) {
		int ret = 0;
		if (root == NULL)
			return ret;
		vector<int> temp;
		dfs(root, temp);
		for (auto i : res) {
			for (auto j : i) {
				cout << j << " ";
			}
			cout << endl;
		}



		for (auto re : res) {
			int sum = 0;
			for (int i = 0, j = re.size() - 1; i<re.size(); i++, j--) {
				sum += re[i] * pow(10, j);
			}
			ret += sum;
		}

		return ret;
	}
};