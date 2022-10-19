#include "headers.h"

class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int s1 = std::count(students.begin(), students.end(), 1);
        int s0 = std::count(students.begin(), students.end(), 0);
        for (int top = 0; top < sandwiches.size(); ++top) {
            if (sandwiches[top] == 1 && s1 > 0) {
                --s1;
            } else if (sandwiches[top] == 0 && s0 > 0) {
                --s0;
            } else {
                break;
            }
        }
        return s1 + s0;
    }
};
