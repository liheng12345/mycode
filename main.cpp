// #include<bits/stdc++.h>
#include <iostream>
#include <thread>
using namespace std;
void test() {
    cout << "hello world!" <<endl;
}
int main() {
    thread mythread(test);
    cout << "hello world!" <<endl;
    system("pause");
    return 0;
}