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
			// ��ǰ��С����һ����cur = cur->next;
			if (cur->val <= next->val)
				cur = next;
			else {
				ListNode* temp = dummy;
				// cur->next ָ��next����һ��
				cur->next = next->next;
				// �ҵ���һ���������
				while (temp->next->val < next->val)
					temp = temp->next;
				next->next = temp->next;
				temp->next = next;
			}

		}
		return dummy->next;
	}
};