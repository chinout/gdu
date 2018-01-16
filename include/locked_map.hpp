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
 private:
    std::mutex _lock;
    std::map<K, V> _map;

 public:
    LockedMap() = default;
    virtual ~LockedMap() = default;

    void insert(const K& key, const V& value) {
        std::lock_guard<std::mutex> g(this->_lock);
        _map.insert(std::make_pair(key, value));
    }

    V find(const K& key) {
        std::lock_guard<std::mutex> g(this->_lock);
        return _map.find(key) == _map.end() ? V() : _map[key];
    }

    bool erase(const K& key) {
        return _map.erase(key);
    }

    void lock() {
        this->_lock.lock();
    }

    void unlock() {
        this->_lock.unlock();
    }

    bool empty() {
        std::lock_guard<std::mutex> g(this->_lock);
        return _map.empty();
    }

    size_t size() {
        std::lock_guard<std::mutex> g(this->_lock);
        return _map.size();
    }
};

}  // namespace gdu 
}  // namespace gdp

#endif  // GDU_LOCKED_MAP_HPP_
