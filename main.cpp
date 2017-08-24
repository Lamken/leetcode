#include <iostream>

using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};


/*class Solution {
public:
    bool isKInGroup(ListNode* head, int k) {
        int counter = 0;
        while(head) {
            head = head->next;
            ++counter;
            if (counter == k) {
                return 1;
            }
        }
        return 0;
    }

    ListNode *reverseKGroup(ListNode *realHead, int k) {
        if (!isKInGroup(realHead, k)) return realHead;
        if (k <= 1) return realHead;
        return reverse(realHead, k, 0);
    }

    ListNode *reverse(ListNode *head, int interval, bool end) {
        if (head == NULL || head->next == NULL)
            return head;

        int k = interval;
        ListNode *init_head = head;
        ListNode *f = head;
        ListNode *b = head->next;

        while (--interval && b) {
            ListNode *temp_next = b->next;
            b->next = f;
            f = b;
            b = temp_next;
        }
        init_head->next = b;
        if (end == 1) return f;
        if (interval != 0) {
            reverse(f, k - interval, 1);
        } else {
            if (isKInGroup(b, k))
                reverse(b, k, end);
        }
        return f;
    }
};*/

class Solution {
public:
    struct Result {
        ListNode *head, *end, *next_head;

        Result() : head(NULL), end(NULL), next_head(NULL) {}

        Result &operator=(Result r) {
            head = r.head;
            next_head = r.next_head;
            end = r.end;
            return *this;
        }
    };

    ListNode *reverseKGroup(ListNode *head, int k) {
        if (k <= 1)
            return head;
        Result result;
        result.next_head = head;
        ListNode *realHead = head;
        int interval = k;
        bool firstGroup = 1;
        while (isKElementInGroup(result.next_head, k)) {
            if (firstGroup) {
                /*  ListNode *f, *b;
                  f = head;
                  b = head->next;
                  while (--interval) {
                      ListNode *temp_next = b->next;
                      b->next = f;
                      f = b;
                      b = temp_next;
                  }
                  head->next = b;
                  realHead = f;
                  head = b;*/
                result = reverse(head, k);
                realHead = result.head;
                firstGroup = 0;
            } else {
                ListNode *last_head = result.end;
                result = reverse(result.next_head, k);
                last_head->next = result.head;
            }
        }
        if (result.end)
            result.end->next = result.next_head;
        return realHead;
    }

    bool isKElementInGroup(ListNode *head, int k) {
        if (!head) return false;
        int counter = 0;
        while (head) {
            ++counter;
            if (counter == k)
                return 1;
            head = head->next;
        }
        return 0;
    }

    Result reverse(ListNode *head, int k) {
        ListNode *f, *b;
        f = head;
        b = head->next;
        while (--k) {
            ListNode *temp_next = b->next;
            b->next = f;
            f = b;
            b = temp_next;
        }
        Result result;
        result.end = head;
        result.next_head = b;
        result.head = f;
        return result;
    }
};

void show(ListNode *head) {
    while (head != NULL) {
        cout << head->val << ' ';
        head = head->next;
    }
}

int main() {
    int num;
    cin >> num;
    int temp_val;
    cin >> temp_val;
    ListNode *head = new ListNode(temp_val);
    ListNode *temp = head;
    for (int i = 0; i < num - 1; ++i) {
        cin >> temp_val;
        temp->next = new ListNode(temp_val);
        temp = temp->next;
    }
    Solution s;
    int k;
    cin >> k;
    head = s.reverseKGroup(head, k);
    show(head);
}