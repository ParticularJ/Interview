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
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int> >  res;
		if (!root)return res;
		queue<pair<TreeNode*, int> > que;
		que.push(make_pair(root, 0));

		while (que.size()>0) {
			pair<TreeNode*, int> front = que.front();
			que.pop();

			if (front.second == res.size())
				res.push_back(vector<int>());

			res[front.second].push_back(front.first->val);

			if (front.first->left) {
				que.push(make_pair(front.first->left, front.second + 1));
			}
			if (front.first->right) {
				que.push(make_pair(front.first->right, front.second + 1));
			}
		}
		return res;
	}
};