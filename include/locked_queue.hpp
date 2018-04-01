// copyright 2017 war10ck

#ifndef GDU_LOCKED_QUEUE_HPP_
#define GDU_LOCKED_QUEUE_HPP_

#include <thread>
#include <mutex>
#include <deque>
#include <algorithm>
#include <utility>

namespace gdp {
namespace gdu {

template <typename T, typename StorageType = std::deque<T> >
class LockedQueue {
 public:
    LockedQueue() = default;
    virtual ~LockedQueue() = default;
    LockedQueue(const LockedQueue<T>&) = delete;
    LockedQueue<T>& operator = (const LockedQueue<T>&) = delete;

    void add(const T& item) {
        std::lock_guard<std::mutex> g(this->mutex_);
        return queue_.emplace_back(item);
    }

    bool next(T& result) {
        std::lock_guard<std::mutex> g(this->mutex_);
        if (queue_.empty()) {
            return false;
        }

        result = queue_.front();
        queue_.pop_front();

        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> g(this->mutex_);
        return queue_.empty();
    }

    size_t size() {
        std::lock_guard<std::mutex> g(this->mutex_);
        return queue_.size();
    }

    void lock() {
        mutex_.lock();
    }

    void unlock() {
        mutex_.unlock();
    }

    // ! get top of the queue. Rember to unlock after use.
    T& peek() {
        lock();

        T& result = queue_.front();

        return result;
    }

    // ! remove element
    bool del(T& r) {
        std::lock_guard<std::mutex> g(this->mutex_);
        typename StorageType::iterator it;
        it = std::find(queue_.begin(), queue_.end(), r);
        if (it != queue_.end()) {
            queue_.erase(it);
            return true;
        }
        return false;
    }


 private:
    StorageType queue_;
    std::mutex mutex_;
};

}  // namespace gdu 
}  // namespace gdp

#endif  // GDU_LOCKED_QUEUE_HPP_
