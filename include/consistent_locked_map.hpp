// copyright 2017 war10ck

#ifndef GDU_CONSISTENT_LOCKED_MAP_HPP_
#define GDU_CONSISTENT_LOCKED_MAP_HPP_

#include <thread>
#include <mutex>
#include <map>
#include <algorithm>
#include <utility>
#include <functional>
#include "hash.hpp"

namespace gdp {
namespace gdu {

template <typename K, typename V>
class ConsistentLockedMap {
 public:
    ConsistentLockedMap() = default;
    virtual ~ConsistentLockedMap() = default;
    ConsistentLockedMap(const ConsistentLockedMap<K, V>&) = delete;
    ConsistentLockedMap<K, V>& operator = (const ConsistentLockedMap<K, V>&) = delete;

    bool insert(const K& hash, const V& node) {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.insert(std::make_pair(hash, node)).second;
    }

    void update(const K& hash, const V& node) {
        std::lock_guard<std::mutex> g(this->mutex_);
        data_[hash] = node;
    }

    bool find(const K& hash, V& node) {
        std::lock_guard<std::mutex> g(this->mutex_);
        if (data_.empty()) {
            return false;
        }

        auto it = data_.lower_bound(hash);

        if (it == data_.end()) {
            it = data_.begin();
        }

        node = it->second;
        return true;
    }

    size_t erase(uint32_t hash) {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.erase(hash);
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

#endif  // GDU_CONSISTENT_LOCKED_MAP_HPP_
