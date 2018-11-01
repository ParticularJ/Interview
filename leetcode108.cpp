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
	TreeNode* createBST(vector<int>& nums, int l, int r) {
		if (l>r)
			return NULL;
		if (l == r)
			return new TreeNode(nums[r]);

		// 以中间结点为根
		int mid = l + (r - l) / 2;
		TreeNode *root = new TreeNode(nums[mid]);
		root->left = createBST(nums, l, mid - 1);
		root->right = createBST(nums, mid + 1, r);
		return root;
	}


	TreeNode* sortedArrayToBST(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return NULL;
		TreeNode* root;
		return createBST(nums, 0, size - 1);
	}
};