#include "headers.h"

class LRUCache {
public:
    explicit LRUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        auto iter = map_.find(key);
        if (iter != map_.end()) {
            auto head_next = list_.insert(std::next(head_), *iter->second);
            list_.erase(iter->second);
            iter->second = head_next;
            return iter->second->value;
        }
        return -1;
    }

    void put(int key, int value) {
        auto iter = map_.find(key);
        if (iter != map_.end()) {
            auto head_next = list_.insert(std::next(head_), *iter->second);
            list_.erase(iter->second);
            iter->second = head_next;
            iter->second->value = value;
        } else {
            if (map_.size() == capacity_) {
                auto last = std::prev(tail_);
                int last_key = last->key;
                list_.erase(last);
                map_.erase(last_key);
            }

            map_[key] = list_.insert(std::next(head_), {key, value});
        }
    }

private:
    int capacity_;
    struct node_t {
        int key;
        int value;
    };
    std::list<node_t> list_{2};
    std::list<node_t>::iterator head_{list_.begin()};
    std::list<node_t>::iterator tail_{std::next(list_.begin())};
    std::unordered_map<int, std::list<node_t>::iterator> map_;
};
