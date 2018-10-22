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
			// ����������
			if (next != NULL && cur->val == next->val) {
				//�ҵ���һ������ȵ�
				while (next != NULL && cur->val == next->val)next = next->next;
				// ��¼��ȵ�ֵ
				int val = cur->val;
				ListNode * temp = cur;
				// ɾ��������ȵĽ��
				while (temp->next != NULL && temp->val == val)
				{
					ListNode *record = temp->next;
					delete temp;
					temp = record;
				}
				// ָ���һ������ȵĽ��
				pre->next = next;
			}
			else {
				pre = cur;
			}
		}
		return dummy->next;
	}
};