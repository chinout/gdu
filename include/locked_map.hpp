// copyright 2017 war10ck

#ifndef GDU_LOCKED_MAP_HPP_
#define GDU_LOCKED_MAP_HPP_

#include <thread>
#include <mutex>
#include <map>
#include <algorithm>
#include <utility>

namespace gdp {
namespace gdu {

template <typename K, typename V>
class LockedMap {
 public:
    LockedMap() = default;
    virtual ~LockedMap() = default;
    LockedMap(const LockedMap<K, V>&) = delete;
    LockedMap<K, V>& operator = (const LockedMap<K, V>&) = delete;

    bool insert(const K& key, const V& value) {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.insert(std::make_pair(key, value)).second;
    }

    void update(const K& key, const V& value) {
        std::lock_guard<std::mutex> g(this->mutex_);
        data_[key] = value;
    }

    bool find(const K& key, V& value) {
        std::lock_guard<std::mutex> g(this->mutex_);
        auto it = data_.find(key);
        if (it == data_.end()) {
            return false;
        }

        value = it->second;
        return true;
    }

    bool erase(const K& key) {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.erase(key);
    }

    bool empty() {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.empty();
    }

    size_t size() {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.size();
    }

    void lock() {
        mutex_.lock();
    }

    void unlock() {
        mutex_.unlock();
    }

 private:
    std::map<K, V> data_;
    std::mutex mutex_;
};

}  // namespace gdu 
}  // namespace gdp

#endif  // GDU_LOCKED_MAP_HPP_
