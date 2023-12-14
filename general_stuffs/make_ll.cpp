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

int main () {
    ListNode *head = make_ll();
    return 0;
}

/*
Time Complexity: O(n)
Space Complexity: O(n)
*/