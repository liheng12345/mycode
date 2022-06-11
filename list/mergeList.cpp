#include<iostream>
using namespace std;

struct mergeList
{
    int val;
    mergeList* next;
    mergeList(int _val): val(_val),next(nullptr) {
    };
};

mergeList* mergeSortList(mergeList* p1, mergeList* p2) {
    mergeList* dummy = new mergeList(-1);
    mergeList* cur = dummy;
    while(p1 && p2) {
        if(p1->val > p2->val) {
            cur->next = p2;
            p2 = p2->next;
            cur = cur->next;
        }else {
            cur->next = p1;
            p1 = p1->next;
            cur = cur->next;
        }
    }
    if(p1!=nullptr) {
        cur->next = p1;
    }else {
        cur->next = p2;
    }
    return dummy->next;
}
int main() {
    mergeList* p1 = new mergeList(1);
    mergeList* p2 = new mergeList(3);
    mergeList* p3 = new mergeList(5);
    p1->next = p2;
    p2->next = p3;
    p3->next = nullptr;
    mergeList* q1 = new mergeList(2);
    mergeList* q2 = new mergeList(4);
    mergeList* q3 = new mergeList(6);
    q1->next = q2;
    q2->next = q3;
    q3->next = nullptr;
    // 开始合并
    mergeList* ans = mergeSortList(p1,q1);
    while(ans) {
        cout << ans->val <<endl;
        ans = ans->next;
    }
    return 0;
}