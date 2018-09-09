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
	void sloved(TreeNode* root, vector<int>& res) {
		if (root) {
			res.push_back(root->val);
			sloved(root->left, res);
			sloved(root->right, res);
		}

	}

	vector<int> preorderTraversal(TreeNode* root) {
		//         vector<int> res;
		//         if(root == NULL)return res;
		//         stack<TreeNode*> que;
		//         que.push(root);
		//         while(que.size()>0){
		//             TreeNode* top = que.top();
		//             res.push_back(top->val);
		//             que.pop();
		//             if(top->right){
		//                 que.push(top->right);
		//             }
		//             if(top->left){
		//                 que.push(top->left);
		//             }
		//         }
		//         return res;
		vector<int> res;
		sloved(root, res);
		return res;
	}
};