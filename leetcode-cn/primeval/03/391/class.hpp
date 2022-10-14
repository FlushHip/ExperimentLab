class Solution {
    inline long long get_area(const std::vector<int> &rect) {
        return (rect[2] - rect[0] + 0ll) * (rect[3] - rect[1]);
    }
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        long long area = 0;
        std::vector<int> target{
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::min(),
        };
        std::map<std::pair<int, int>, int> has;
        for (const auto &rect : rectangles) {
            area += get_area(rect);

            target[0] = std::min(target[0], rect[0]);
            target[1] = std::min(target[1], rect[1]);
            target[2] = std::max(target[2], rect[2]);
            target[3] = std::max(target[3], rect[3]);

            ++has[{ rect[0], rect[1] }];
            ++has[{ rect[0], rect[3] }];
            ++has[{ rect[2], rect[1] }];
            ++has[{ rect[2], rect[3] }];
        }
        std::vector<std::pair<int, int>> endpoints{
            { target[0], target[1] },
            { target[0], target[3] },
            { target[2], target[1] },
            { target[2], target[3] },
        };
        if (!std::all_of(endpoints.begin(), endpoints.end(), [&has](const auto &ele)
        {
            return has[ele] == 1;
        })) {
            return false;
        }

        for_each(endpoints.begin(), endpoints.end(), [&has](const auto &ele)
        {
            has.erase(ele);
        });
        return std::all_of(has.begin(), has.end(), [](const auto &ele)
        {
            return ele.second == 2 || ele.second == 4;
        }) && area == get_area(target);
    }
};
