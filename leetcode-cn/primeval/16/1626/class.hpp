#include "headers.h"

class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        struct person {
            int age;
            int score;
        };
        int n = static_cast<int>(scores.size());
        std::vector<person> persons;
        persons.reserve(n);
        for (int i = 0; i < n; ++i) {
            persons.emplace_back(person{ages[i], scores[i]});
        }
        std::sort(persons.begin(), persons.end(),
            [](const person& lhs, const person& rhs) {
                return lhs.age == rhs.age ? lhs.score < rhs.score
                                          : lhs.age < rhs.age;
            });
        std::vector<int> dp(n);
        dp[0] = persons[0].score;
        for (int i = 1; i < n; ++i) {
            int max_value = 0;
            for (int j = i - 1; j >= 0; --j) {
                if (persons[i].score >= persons[j].score) {
                    max_value = std::max(max_value, dp[j]);
                }
            }
            dp[i] = persons[i].score + max_value;
        }
        return *std::max_element(dp.begin(), dp.end());
    }
};
