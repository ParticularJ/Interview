/**
* Definition for binary tree with next pointer.
* struct TreeLinkNode {
*  int val;
*  TreeLinkNode *left, *right, *next;
*  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
* };
*/    
class Solution {
public:
	void dfs(TreeLinkNode* res, TreeLinkNode* temp) {
		if(temp != NULL){
			temp->next = res;
		}
		if (res->left != NULL) {
			dfs(res->left, (temp == NULL)?NULL:temp->right);
		}
		if (res->right != NULL) {
			dfs(res->right, res->left);
		}
	}
	void connect(TreeLinkNode *root) {
		if (root == NULL)return;
		dfs(root, NULL);
	}
};