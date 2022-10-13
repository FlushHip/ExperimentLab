class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        std::map<std::string, unsigned int> listMap;
        for (auto i = 0u; i < list1.size(); ++i) {
            listMap[list1[i]] = i;
        }
        std::map<unsigned int, std::vector<std::string>> ans;
        for (auto i = 0u; i < list2.size(); ++i) {
            if (listMap.find(list2[i]) != listMap.end()) {
                ans[i + listMap[list2[i]]].push_back(list2[i]);
            }
        }
        return ans.begin()->second;
    }
};
