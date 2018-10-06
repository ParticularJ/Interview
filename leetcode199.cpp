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
	vector<int> rightSideView(TreeNode* root) {
		vector<int> res;
		if (root == NULL)return res;
		queue<TreeNode* > q;
		q.push(root);
		while (q.size()) {
			res.push_back(q.back()->val);
			// 将当前层的都pop出去，最后一个push的即为最右侧
			for (int i = q.size(); i>0; i--) {
				TreeNode* f = q.front();
				q.pop();
				if (f->left)q.push(f->left);
				if (f->right)q.push(f->right);
			}

		}
		return res;
	}
};