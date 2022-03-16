class AllOne {
    std::unordered_map<std::string, int> first_map_;
    std::multimap<int, std::string> second_map_;
public:
    AllOne() {}

    void inc(string key) {
        auto cnt = ++first_map_[key];
        auto [lhs, rhs] = second_map_.equal_range(cnt - 1);
        if (lhs == rhs) {
            second_map_.emplace(cnt, std::move(key));
            return;
        }
        for (auto it = lhs; it != rhs; ++it) {
            if (it->second == key) {
                second_map_.erase(it);
                second_map_.emplace(cnt, std::move(key));
                break;
            }
        }
    }

    void dec(string key) {
        auto cnt = --first_map_[key];
        if (!cnt) {
            first_map_.erase(key);
        }
        auto [lhs, rhs] = second_map_.equal_range(cnt + 1);
        for (auto it = lhs; it != rhs; ++it) {
            if (it->second == key) {
                second_map_.erase(it);
                if (cnt) {
                    second_map_.emplace(cnt, std::move(key));
                }
                break;
            }
        }
    }

    string getMaxKey() {
        return second_map_.empty() ? ""s : second_map_.rbegin()->second;
    }

    string getMinKey() {
        return second_map_.empty() ? ""s : second_map_.begin()->second;
    }
};
