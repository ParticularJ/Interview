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
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode *dummp = new ListNode(0);
		dummp->next = head;
		ListNode *pre = dummp;
		ListNode *next = head;
		while (n >= 1) {
			next = next->next;
			n--;
		}

		while (next != NULL) {
			next = next->next;
			pre = pre->next;
		}
		// delNode ¼ÇÒä±ãÓÚÉ¾³ý

		ListNode *delNode = pre->next;
		pre->next = delNode->next;
		delete delNode;
		return dummp->next;
	}
};