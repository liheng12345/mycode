#include <bits/stdc++.h>
using namespace std;

class threadPool {
    private:
        int threadNum;
        vector<int> workqueue;
        vector<pthread_t> m_threads;
        pthread_mutex_t mutex;
        pthread_cond_t m_cond;
    public:
        threadPool():threadNum(4) {
            m_threads.resize(threadNum);
            // 初始化互斥量、信号量
            pthread_mutex_init(&mutex, NULL);
            pthread_cond_init(&m_cond, nullptr);
            // 构造线程池
            for(int i = 0 ; i < threadNum; i++) {
                pthread_create(&m_threads[i], nullptr, worker, this);
            }
            // 在主线程对工作线程进行分离
            for(int i = 0 ; i < threadNum; i++) {
                pthread_detach(m_threads[i]);
            }
        }
        // 主线程负责添加数据
        void appentData(int a);
        // 必须是静态的
        static void* worker(void* arg);
        void run();
};
void threadPool::appentData(int a) {
    pthread_mutex_lock(&mutex);
    workqueue.push_back(a);
    pthread_mutex_unlock(&mutex);
    if(workqueue.size() > 0) {
        pthread_cond_signal(&m_cond);
    }
    return;
}
void* threadPool::worker(void* arg) {
    threadPool* m_pool = (threadPool*)arg;
    m_pool->run();
    return m_pool;
}
void threadPool::run() {
    // 子线程一直运行
    while(true) {
        // 先上锁
        pthread_mutex_lock(&mutex);
        while(workqueue.size() == 0) {
            // 无资源，阻塞并且解锁，以便主线程拿到锁去加入数据。有资源跳出循环，并重新上锁。
            pthread_cond_wait(&m_cond, &mutex);
        }
        // 此时必然是有资源的
        int data = workqueue.back();
        workqueue.pop_back();
        cout << data << endl;
        pthread_mutex_unlock(&mutex);
    }
    return;
}
int main() {
    threadPool* test = new threadPool();
    for(int i = 0; i < 10; i++) {
        test->appentData(i);
    }
    system("pause");
    return 0;
}