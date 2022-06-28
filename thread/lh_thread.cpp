#include <bits/stdc++.h>
// 信号量的头文件
#include <semaphore.h>
using namespace std;

class threadPool {
    private:
        int threadNum;
        vector<int> workqueue;
        vector<pthread_t> m_threads;
        pthread_mutex_t mutex;
        sem_t m_sem;
    public:
        threadPool():threadNum(4) {
            m_threads.resize(threadNum);
            // 初始化互斥量、信号量
            pthread_mutex_init(&mutex, NULL);
            // 第二次参数设置为0代表该信号量可以线程之间共享
            sem_init(&m_sem, 0, 0 );
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
    sem_post( &m_sem );
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
        sem_wait(&m_sem);
        pthread_mutex_lock(&mutex);
        if(workqueue.empty()) {
            pthread_mutex_unlock(&mutex);
            continue;
        }
        int data = workqueue.back();
        workqueue.pop_back();
        cout << data << endl;
        pthread_mutex_unlock(&mutex);
    }
    return;
}
int main() {
    threadPool* test = new threadPool();
    for(int i = 0; i < 100; i++) {
        test->appentData(i);
    }
    system("pause");
    return 0;
}