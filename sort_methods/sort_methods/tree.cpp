#include<iostream>
#include<vector>
#include<ctime>
#include<cassert>
#include<ctime>
#include<algorithm>
#include<functional>
#include<queue>

using namespace std;

template<typename Key>
class BST {
private:
	struct TreeNode{
		Key  val;
		TreeNode* left, *right;
		TreeNode(Key val, TreeNode *left) {
			this->val = val;
			this->left = this->right = NULL;
		}
	};
public:
	TreeNode* levelOrder(TreeNode* root) {
		queue<TreeNode*> myque;
		myque.push(root);
		while (myque.size() > 0) {
			TreeNode* front = myque.front();
			myque.pop();
			if (front->left) {
				myque.push(front->left);
			}
			if (front->right) {
				myque.push(front->right);
			}
		} 
	}

};