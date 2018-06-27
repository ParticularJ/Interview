/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/

/*
  �����ǰ�к����������Ҫ���ʣ�ʹ�õݹ鼴�ɽ����
           1
          / \
		 2   3
		/\   /\
	   4  5 6  7
   preorder [1, 2, 4, 5, 3, 6 , 7]
   inorder [4, 2, 5, 1, 6, 3, 7]
   postorder [4, 5, 2, 6, 7, 3, 1]
   ���ԣ���������ĸ��϶������һ��λ�ã� ǰ��Ϊ��һ��λ�ã� ������Ϊ�м�
   ���У����������߾�Ϊ���ӣ��ұ߾�Ϊ�к���
   ǰ�������ǰ��Ϊ���ӣ�����Ϊ�Һ���
   ���������ǰ��Ϊ���ӣ�����Ϊ�Һ���
*/
class Solution {
public:
	vector<int> pre, in;
	TreeNode *build(int pl, int pr, int il, int ir) {
		if (pl > pr)
			return NUll;
		int root_val = pre[pl];
		int val_in = il - 1;
		for (int il; il <= ir; i++) {
			if (in[il] == root_val)
				val_in = il;
		}
		TreeNode *res = New TreeNode(root_val);
		int len_left = val_in - il;
		res->left = build(pl+1, pl+len_left-1, il, val_in - 1);
		res->right = build( pl+len_left, pr, val_in + 1, ir);
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		int size = preorder.size();
		pre = preorder;
		in = inorder;
		return build(0, size - 1, 0, size - 1);
	}
};