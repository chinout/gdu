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

    typename std::map<K, V>::iterator find(const K& key) {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.find(key);
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

    typename std::map<K, V>::iterator begin() {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.begin();
    }

    typename std::map<K, V>::iterator end() {
        std::lock_guard<std::mutex> g(this->mutex_);
        return data_.end();
    }
 private:
    std::map<K, V> data_;
    std::mutex mutex_;
};

}  // namespace gdu 
}  // namespace gdp

#endif  // GDU_LOCKED_MAP_HPP_
