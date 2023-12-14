#include <bits/stdc++.h>
using namespace std;

class ListNode {
    public:
        int val;
        ListNode *next;

        ListNode () : val(0), next(NULL) {}
        ListNode (int val) : val(val), next(NULL) {}

        ~ListNode () {
            delete this->next;
        }
};

ListNode *make_ll() {
    int n;
    cin>>n;

    ListNode *head = NULL;
    ListNode *tail = NULL;

    while(n--) {
        int input;
        cin>>input;

        ListNode *temp = new ListNode(input);
        if(!head) head = tail = temp;
        else {
            tail->next = temp;
            tail = tail->next;
        }
    }
    return head;
}

ListNode *merge_sort_ll(ListNode *head) {
    if(!head || !head->next) return head;

    ListNode *slow = head;
    ListNode *fast = head->next;

    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *h2 = merge_sort_ll(slow->next);
    slow->next = NULL;

    ListNode *h1 = merge_sort_ll(head);
    ListNode *tail = NULL;
    
    if(h1->val<=h2->val) {
        head = tail = h1;
        h1 = h1->next;
    }
    else {
        head = tail = h2;
        h2 = h2->next;
    }

    while(h1 && h2) {
        if(h1->val<=h2->val) {
            tail->next = h1;
            h1 = h1->next;
            tail = tail->next;
        }
        else {
            tail->next = h2;
            h2 = h2->next;
            tail = tail->next;
        }
    }
    if(h1) tail->next = h1;
    else if(h2) tail->next = h2;

    return head;
}

void print_ll(ListNode *head) {
    ListNode *curr = head;
    while(curr) {
        cout<<curr->val<<" -> ";
        curr = curr->next;
    }
    cout<<"NULL"<<endl;
}

int main () {
    ListNode *head = make_ll();
    print_ll(merge_sort_ll(head));
    return 0;
}

/*
Time Complexity: O(n*logn)
Space Complexity: O(1)
*/