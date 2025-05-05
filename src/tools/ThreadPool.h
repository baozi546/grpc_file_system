#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <atomic>
#include <memory>
class ThreadPool {
public:
    // ���캯��������ָ�������Ĺ����߳�
    explicit ThreadPool(size_t threads);
    // ��������̳߳أ�����future�Ա��ȡ���
    template<class F, class ...Args>
    inline auto enqueue(F&& f, Args && ...args) -> std::future<typename std::invoke_result_t<F, Args ...>>
    {
        using return_type = typename std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");

            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    // ��ȡΨһ�̳߳�
    static ThreadPool& Get();
    ~ThreadPool();// ��ȫֹͣ�̳߳أ��ȴ�����������ɣ�

private:
    // ���캯��������ָ�������Ĺ����߳�
    std::vector<std::thread> workers;    // �����߳�
    std::queue<std::function<void()>> tasks; // �������
    std::mutex queue_mutex;              // ���л�����
    std::condition_variable condition;   // ��������
    std::atomic<bool> stop;              // ֹͣ��־

};


#endif // !


