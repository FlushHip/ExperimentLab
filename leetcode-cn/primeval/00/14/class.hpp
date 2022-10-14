class Solution {
    struct Node{
        enum { MAX_LEN = 26 };
        unsigned cnt = 0;
        std::shared_ptr<Node> next[MAX_LEN];
    };
    std::shared_ptr<Node> root_;

    inline int get_next(char c) {
        return c - 'a';
    }
public:
    string longestCommonPrefix(vector<string>& strs) {
        root_ = std::make_shared<Node>();
        for (const auto &str : strs) {
            auto ptr = root_;
            for (const auto c : str) {
                if (nullptr == ptr->next[get_next(c)]) {
                    ptr->next[get_next(c)] = std::make_shared<Node>();
                }
                ptr = ptr->next[get_next(c)];
                ++ptr->cnt;
            }
        }

        std::string ans;
        for (auto ptr = root_; ptr != nullptr; ) {
            int c = 0, cnt = 0;
            for (int i = 0; i < Node::MAX_LEN; ++i) {
                if (ptr->next[i] != nullptr) {
                    c = i;
                    ++cnt;
                }
            }
            if (cnt == 1 && ptr->next[c]->cnt == strs.size()) {
                ans.push_back(c + 'a');
                ptr = ptr->next[c];
            } else {
                break;
            }
        }

        return ans;
    }
};
