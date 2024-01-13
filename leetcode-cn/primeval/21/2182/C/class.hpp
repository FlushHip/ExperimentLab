#include "headers.h"

class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        constexpr unsigned int alpha_length = 26;
        std::array<int, alpha_length> line{};
        for (const char c : s) {
            assert(std::islower(c));
            ++line[c - 'a'];
        }
        string ret;
        enum class state_t { first, second } state{state_t::first};
        for (int index{}, f = true; f;) {
            f = true;
            switch (state) {
            case state_t::first:
                for (index = alpha_length - 1; index >= 0 && 0 == line[index];
                     --index) {
                }
                if (index < 0) {
                    f = false;
                    break;
                }
                if (line[index] > repeatLimit) {
                    line[index] -= repeatLimit;
                    state = state_t::second;
                    ret.append(repeatLimit, index + 'a');
                } else {
                    ret.append(line[index], index + 'a');
                    line[index] = 0;
                }
                break;
            case state_t::second:
                for (index = alpha_length - 1; index >= 0 &&
                     (0 == line[index] || ret.back() - 'a' == index);
                     --index) {
                }
                if (index < 0) {
                    f = false;
                    break;
                }
                state = state_t::first;
                ret.push_back(index + 'a');
                line[index] -= 1;
                break;
            }
        }
        return ret;
    }
};
