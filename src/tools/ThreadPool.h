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
    // 构造函数，启动指定数量的工作线程
    explicit ThreadPool(size_t threads);
    // 添加任务到线程池，返回future以便获取结果
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

    // 获取唯一线程池
    static ThreadPool& Get();
    ~ThreadPool();// 安全停止线程池（等待所有任务完成）

private:
    // 构造函数，启动指定数量的工作线程
    std::vector<std::thread> workers;    // 工作线程
    std::queue<std::function<void()>> tasks; // 任务队列
    std::mutex queue_mutex;              // 队列互斥锁
    std::condition_variable condition;   // 条件变量
    std::atomic<bool> stop;              // 停止标志

};


#endif // !


