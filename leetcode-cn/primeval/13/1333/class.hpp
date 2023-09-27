#include "headers.h"

class Solution {
public:
    vector<int> filterRestaurants(vector<vector<int>>& restaurants,
        int veganFriendly,
        int maxPrice,
        int maxDistance) {
        auto end = std::partition(restaurants.begin(), restaurants.end(),
            [=](const std::vector<int>& restaurant) {
                return (!veganFriendly || restaurant[2] == veganFriendly) &&
                    restaurant[3] <= maxPrice && restaurant[4] <= maxDistance;
            });
        std::sort(
            restaurants.begin(), end, [](const auto& lhs, const auto& rhs) {
                return lhs[1] == rhs[1] ? lhs[0] > rhs[0] : lhs[1] > rhs[1];
            });
        std::vector<int> ans(std::distance(restaurants.begin(), end));
        std::transform(restaurants.begin(), end, ans.begin(),
            [](const auto& resaurant) { return resaurant[0]; });
        return ans;
    }
};
