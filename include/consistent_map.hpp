// copyright 2017 war10ck

#ifndef GDU_CONSISTENT_MAP_HPP_
#define GDU_CONSISTENT_MAP_HPP_

#include <thread>
#include <mutex>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <functional>
#include "hash.hpp"

namespace gdp {
namespace gdu {

template <typename K, typename V>
class ConsistentMap {
 public:
    ConsistentMap() = default;
    virtual ~ConsistentMap() = default;
    ConsistentMap(const ConsistentMap<K, V>&) = delete;
    ConsistentMap<K, V>& operator = (const ConsistentMap<K, V>&) = delete;

    bool insert(const K& hash, const V& node) {
        return data_.insert(std::make_pair(hash, node)).second;
    }

    void update(const K& hash, const V& node) {
        data_[hash] = node;
    }

    bool find(const K& hash, V& node) {
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
        return data_.erase(hash);
    }

    bool empty() {
        return data_.empty();
    }

    size_t size() {
        return data_.size();
    }

 private:
    std::unordered_map<K, V> data_;
};

}  // namespace gdu 
}  // namespace gdp

#endif  // GDU_CONSISTENT_MAP_HPP_
