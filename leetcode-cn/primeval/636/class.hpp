#include "headers.h"

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        struct ctx {
            int id;
            int start_stamp;
        };
        std::stack<ctx> st;
        std::vector<int> result(n, 0);

        for (const auto& lg : logs) {
            std::istringstream iss(lg);
            std::string line;

            int id = 0;
            int time_stamp = 0;
            enum : int { kstart, kend } type{};

            std::getline(iss, line, ':');
            id = std::stoi(line);
            std::getline(iss, line, ':');
            type = line.front() == 's' ? kstart : kend;
            std::getline(iss, line);
            time_stamp = stoi(line);

            if (type == kstart) {
                if (!st.empty()) {
                    result[st.top().id] += time_stamp - st.top().start_stamp;
                }
                st.emplace(ctx{id, time_stamp});
            } else {
                result[st.top().id] += time_stamp - st.top().start_stamp + 1;
                st.pop();
                if (!st.empty()) {
                    st.top().start_stamp = time_stamp + 1;
                }
            }
        }

        return result;
    }
};
