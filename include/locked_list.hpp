// copyright 2017 war10ck

#ifndef GDU_LOCKED_LIST_HPP_
#define GDU_LOCKED_LIST_HPP_

#include <thread>
#include <mutex>
#include <list>
#include <algorithm>
#include <utility>

namespace gdp {
namespace gdu {

template <typename T>
class LockedList {
 public:
    LockedList() = default;
    virtual ~LockedList() = default;
    LockedList(const LockedList<T>&) = delete;
    LockedList<T>& operator = (const LockedList<T>&) = delete;

    void push_back(const T& value) {
        std::lock_guard<std::mutex> g(this->mutex_);
        data_.push_back(value);
    }

    T front() {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.front();
    }

    void pop_front() {
        std::lock_guard<std::mutex> g(this->mutex_);
        data_.pop_front();
    }

    void emplace_back(const T& value) {
        std::lock_guard<std::mutex> g(this->mutex_);
        data_.emplace_back(value);
    }

    bool empty() {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.empty();
    }

    size_t size() {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.size();
    }

    // ! get top of the queue. Rember to unlock after use.
    T& peek() {
        lock();

        T& result = data_.front();

        return result;
    }

    void lock() {
        mutex_.lock();
    }

    void unlock() {
        mutex_.unlock();
    }

 private:
    std::list<T> data_;
    std::mutex mutex_;
};

}  // namespace gdu 
}  // namespace gdp

#endif  // GDU_LOCKED_MAP_HPP_
