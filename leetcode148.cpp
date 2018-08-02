/*
merge_sort : 归并排序
top_down（递归法）: time complexity: O(nlogn) space complexicity O(logn)
	1、 申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列
	2、 设定快慢指针， 最初位置分别为两个已经排序序列的起始位置
	3、 比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置
	4、 重复3到达队尾
	5、 将另一序列剩下的所有元素直接复制到合并序列尾

bottom up（迭代法）: time : O(nlogn) space O(1)
	1、 将序列每相邻两个数字进行归并排序， 形成（n/2）个序列，
	2、 若序列不为1，则再次归并， 
	3、 重复2， 知道排列完毕
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
	// 递归的求解方法 space O(logn)
	ListNode* sortList1(ListNode* head) {
		if (head == NULL||head->next==NULL)return head;
		ListNode* fast = head->next;
		ListNode* slow = head;
		// 快慢指针，从中断开，慢指针刚好是位于链表的中间。
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		//从中断开
		ListNode* mid = slow->next;
		slow->next = nullptr;
		return mergesort(sortList(head), sortList(mid));
	}
	ListNode* mergesort(ListNode* l1, ListNode* l2) {
		//傀儡结点
		ListNode dummy(0);
		ListNode* tail = &dummy;
		while (l1 && l2) {
			if (l1->val > l2->val)swap(l1, l2);
			// tail指向head节点
			tail->next = l1;
			// 分别向后移动一位
			l1 = l1->next;
			tail = tail->next;
		}
		if (l1)tail->next = l1;
		if (l2)tail->next = l2;
		return dummy.next;
public:
	//迭代的求解方法， space O(1)
	ListNode* sortList2(ListNode* head) {
	
		}
	}
};