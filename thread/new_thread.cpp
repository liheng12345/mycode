#include<bits/stdc++.h>
using namespace std;
void *test(void* arg) {
    int a = *(int*)arg;
    cout << a<<endl;
    return((void *)0);
}
int main() {

    pthread_t one;
    int x = 7;
    pthread_create(&one,nullptr,test,&x);
    pthread_join(one,nullptr);
    system("pause");
    return 0;
}