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
	ListNode* insertionSortList(ListNode* head) {
		ListNode * dummy = new ListNode(0);
		dummy->next = head;
		if (head == NULL)return NULL;
		ListNode* pre = dummy;
		ListNode* cur = pre->next;

		while (cur->next != NULL) {
			ListNode* next = cur->next;
			// 当前的小于下一个，cur = cur->next;
			if (cur->val <= next->val)
				cur = next;
			else {
				ListNode* temp = dummy;
				// cur->next 指向next的下一个
				cur->next = next->next;
				// 找到第一个比它大的
				while (temp->next->val < next->val)
					temp = temp->next;
				next->next = temp->next;
				temp->next = next;
			}

		}
		return dummy->next;
	}
};