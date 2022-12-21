#include "headers.h"

class LFUCache {
public:
    explicit LFUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        auto iter = keys_.find(key);
        if (iter == keys_.end()) {
            return -1;
        }
        ctx context = *iter->second;
        freqs_[context.freq].erase(iter->second);
        keys_.erase(key);
        if (freqs_[context.freq].empty() && min_freq_ == context.freq) {
            ++min_freq_;
        }

        ++context.freq;
        keys_[key] =
            freqs_[context.freq].insert(freqs_[context.freq].begin(), context);
        return context.value;
    }

    void put(int key, int value) {
        if (capacity_ == 0) {
            return;
        }
        auto iter = keys_.find(key);
        if (iter != keys_.end()) {
            ctx context = *iter->second;
            freqs_[context.freq].erase(iter->second);
            keys_.erase(key);
            if (freqs_[context.freq].empty() && min_freq_ == context.freq) {
                ++min_freq_;
            }

            ++context.freq;
            context.value = value;
            keys_[key] = freqs_[context.freq].insert(
                freqs_[context.freq].begin(), context);
        } else {
            if (keys_.size() == capacity_) {
                auto last = std::prev(freqs_[min_freq_].end());
                keys_.erase(last->key);
                freqs_[min_freq_].erase(last);
            }
            ctx context{key, value, 1};
            keys_[key] = freqs_[context.freq].insert(
                freqs_[context.freq].begin(), context);
            min_freq_ = 1;
        }
    }

private:
    int capacity_;
    struct ctx {
        int key;
        int value;
        int freq;
    };
    std::unordered_map<int, std::list<ctx>> freqs_;
    std::unordered_map<int, std::list<ctx>::iterator> keys_;
    int min_freq_{0};
};
