/*
merge_sort : �鲢����
top_down���ݹ鷨��: time complexity: O(nlogn) space complexicity O(logn)
	1�� ����ռ䣬ʹ���СΪ�����Ѿ���������֮�ͣ��ÿռ�������źϲ��������
	2�� �趨����ָ�룬 ���λ�÷ֱ�Ϊ�����Ѿ��������е���ʼλ��
	3�� �Ƚ�����ָ����ָ���Ԫ�أ�ѡ�����С��Ԫ�ط��뵽�ϲ��ռ䣬���ƶ�ָ�뵽��һλ��
	4�� �ظ�3�����β
	5�� ����һ����ʣ�µ�����Ԫ��ֱ�Ӹ��Ƶ��ϲ�����β

bottom up����������: time : O(nlogn) space O(1)
	1�� ������ÿ�����������ֽ��й鲢���� �γɣ�n/2�������У�
	2�� �����в�Ϊ1�����ٴι鲢�� 
	3�� �ظ�2�� ֪���������
*/

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
	// �ݹ����ⷽ�� space O(logn)
	ListNode* sortList1(ListNode* head) {
		if (head == NULL||head->next==NULL)return head;
		ListNode* fast = head->next;
		ListNode* slow = head;
		// ����ָ�룬���жϿ�����ָ��պ���λ��������м䡣
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		//���жϿ�
		ListNode* mid = slow->next;
		slow->next = nullptr;
		return mergesort(sortList(head), sortList(mid));
	}
	ListNode* mergesort(ListNode* l1, ListNode* l2) {
		//���ܽ��
		ListNode dummy(0);
		ListNode* tail = &dummy;
		while (l1 && l2) {
			if (l1->val > l2->val)swap(l1, l2);
			// tailָ��head�ڵ�
			tail->next = l1;
			// �ֱ�����ƶ�һλ
			l1 = l1->next;
			tail = tail->next;
		}
		if (l1)tail->next = l1;
		if (l2)tail->next = l2;
		return dummy.next;
public:
	//��������ⷽ���� space O(1)
	ListNode* sortList2(ListNode* head) {
	
		}
	}
};