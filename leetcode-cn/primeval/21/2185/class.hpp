#include "headers.h"

class Solution {
public:
    int prefixCount(vector<string>& words, string pref) {
        tree root;
        for (std::string_view word : words) {
            add(root, word);
        }
        return find(root, pref);
    }

private:
    struct tree {
        int cnt_{0};
        enum { max_child_num = 26 };
        std::array<std::unique_ptr<tree>, max_child_num> childs_;
    };

    inline static int get_index(char c) { return c - 'a'; }

    static void add(tree& root, std::string_view word) {
        tree* p = &root;
        for (char c : word) {
            if (p->childs_[get_index(c)] == nullptr) {
                p->childs_[get_index(c)] = std::make_unique<tree>();
            }
            p = p->childs_[get_index(c)].get();
            ++p->cnt_;
        }
    }

    static int find(const tree& root, std::string_view pref) {
        const tree* p = &root;
        for (char c : pref) {
            if (p->childs_[get_index(c)] == nullptr) {
                return 0;
            }
            p = p->childs_[get_index(c)].get();
        }
        return p->cnt_;
    }
};
