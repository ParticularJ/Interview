/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		ListNode* dummy = new ListNode(0);
		dummy->next = head;
		ListNode* pre = dummy;

		while (pre->next) {
			ListNode* cur = pre->next;
			ListNode* next = cur->next;
			// 如果两个相等
			if (next != NULL && cur->val == next->val) {
				//找到第一个不相等的
				while (next != NULL && cur->val == next->val)next = next->next;
				// 记录相等的值
				int val = cur->val;
				ListNode * temp = cur;
				// 删除所有相等的结点
				while (temp->next != NULL && temp->val == val)
				{
					ListNode *record = temp->next;
					delete temp;
					temp = record;
				}
				// 指向第一个不相等的结点
				pre->next = next;
			}
			else {
				pre = cur;
			}
		}
		return dummy->next;
	}
};