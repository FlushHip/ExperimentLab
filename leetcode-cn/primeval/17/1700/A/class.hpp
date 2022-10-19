#include "headers.h"

class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        std::queue<int> s_students;
        for (auto ele : students) {
            s_students.push(ele);
        }
        std::stack<int> s_sandwiches;
        for (auto it = sandwiches.rbegin(); it != sandwiches.rend(); ++it) {
            s_sandwiches.push(*it);
        }
        for (int cnt = 0; !s_students.empty();) {
            if (s_students.front() == s_sandwiches.top()) {
                s_students.pop();
                s_sandwiches.pop();
                cnt = 0;
            } else {
                int s = s_students.front();
                s_students.pop();
                s_students.push(s);
                ++cnt;
            }
            if (cnt == s_students.size()) {
                return cnt;
            }
        }
        return 0;
    }
};
