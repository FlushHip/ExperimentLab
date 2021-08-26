class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int ans = 0;
        std::sort(people.begin(), people.end());

        int l = 0, r = (int)people.size() - 1;
        while (l + 1 <= r) {
            ++ans;
            if (people[l] + people[r] <= limit) {

                ++l;
                --r;
            } else {
                --r;
            }
        }
        if (l == r) {
            ++ans;
        }
        return ans;
    }
};
