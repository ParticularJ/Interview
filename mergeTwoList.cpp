#include<iostream>
#include<vector>
#include<string>
#include<list>

using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    //构造函数，初始化
    ListNode(int x): val(x), next(NULL) {}
};



class Solution{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2){
        //Dummy node 就是在链表表头 head 前加一个节点指向head
        ListNode dummy(INT_MIN);
        ListNode *tail=&dummy;

        while(l1 && l2){
            if(l1->val < l2->val){
                tail->next = l1;
                l1 = l1->next;
            }
            else{
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1:l2;
        return dummy.next;
    }
};


int main(){
    Solution merge;
    list<int> l1=(1,2,3);
    list<int> l2=(1,2,4);
    cout<<merge.mergeTwoLists(l1, l2);
}
