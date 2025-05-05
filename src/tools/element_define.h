#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <mutex>
#include <shared_mutex>
template<typename T>
class TaskQueue {
public:
	TaskQueue() {};

	bool add_Task(std::string file_id, std::shared_ptr<T> metedata);
	
	bool remove_Task(std::string file_id);

	std::shared_ptr<T> get_Task(std::string file_id);


private:
	std::map<std::string, std::shared_ptr<T>> task_queue_;
	std::shared_mutex mutex_;
};

template<typename T>
inline bool TaskQueue<T>::add_Task(std::string file_id, std::shared_ptr<T> metedata)
{
	std::unique_lock<std::shared_mutex> lock(mutex_);

	if (task_queue_.find(file_id) == task_queue_.end()) {
        task_queue_[file_id] = metedata;
		return true;
	}
	return false;
}

template<typename T>
inline bool TaskQueue<T>::remove_Task(std::string file_id)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);

    if (task_queue_.contains(file_id)) {
        task_queue_.erase(file_id);
        return true;
    }
	return false;
}

template<typename T>
inline std::shared_ptr<T> TaskQueue<T>::get_Task(std::string file_id)
{
	if (task_queue_.contains(file_id)) {
        return task_queue_[file_id];
	}
    return nullptr;
}

