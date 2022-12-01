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
            return iter->second->second;
        }
        return -1;
    }

    void put(int key, int value) {
        auto iter = map_.find(key);
        if (iter != map_.end()) {
            auto head_next = list_.insert(std::next(head_), *iter->second);
            list_.erase(iter->second);
            iter->second = head_next;
            iter->second->second = value;
        } else if (map_.size() == capacity_) {
            auto last = std::prev(tail_);
            int last_key = last->first;
            list_.erase(last);
            map_.erase(last_key);

            map_[key] = list_.insert(std::next(head_), {key, value});
        } else {
            map_[key] = list_.insert(std::next(head_), {key, value});
        }
    }

private:
    int capacity_;
    std::list<std::pair<int, int>> list_{2};
    std::list<std::pair<int, int>>::iterator head_{list_.begin()};
    std::list<std::pair<int, int>>::iterator tail_{std::next(list_.begin())};
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map_;
};
