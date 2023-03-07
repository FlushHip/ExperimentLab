#include "headers.h"

class LFUCache {
public:
    explicit LFUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        if (auto it = keys_.find(key); it != keys_.end()) {
            auto cache = *it->second;
            pq_.erase(it->second);
            keys_.erase(it);

            ++cache.freq;
            cache.timestamp = ++timestamp_;

            auto [iter, _] = pq_.emplace(cache);
            keys_.emplace(key, iter);

            return cache.value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (capacity_ == 0) {
            return;
        }
        if (auto it = keys_.find(key); it != keys_.end()) {
            auto cache = *it->second;
            pq_.erase(it->second);
            keys_.erase(it);

            ++cache.freq;
            cache.timestamp = ++timestamp_;
            cache.value = value;

            auto [iter, _] = pq_.emplace(cache);
            keys_.emplace(key, iter);
        } else {
            if (pq_.size() == capacity_) {
                keys_.erase(pq_.begin()->key);
                pq_.erase(pq_.begin());
            }
            auto [iter, _] = pq_.emplace(ctx{key, value, 1, ++timestamp_});
            keys_.emplace(key, iter);
        }
    }

private:
    int capacity_, timestamp_{0};
    struct ctx {
        int key;
        int value;
        int freq;
        int timestamp;

        bool operator<(const ctx& other) const {
            return freq == other.freq ? timestamp < other.timestamp
                                      : freq < other.freq;
        }
    };
    std::set<ctx> pq_;
    std::unordered_map<int, std::set<ctx>::iterator> keys_;
};
