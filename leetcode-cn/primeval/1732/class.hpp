class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        std::partial_sum(gain.begin(), gain.end(), gain.begin());
        return std::max(0, *std::max_element(gain.begin(), gain.end()));
    }
};
