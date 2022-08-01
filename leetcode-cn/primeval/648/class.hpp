#include "headers.h"

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        std::stable_sort(dictionary.begin(), dictionary.end(),
            [](const std::string& a, const std::string& b) {
                return a.size() < b.size();
            });
        std::stringstream ss(sentence);
        std::string result;
        for (std::string str; ss >> str;) {
            bool f = false;
            for (const auto& root : dictionary) {
                if (str.size() > root.size() &&
                    std::equal(root.begin(), root.end(), str.begin(),
                        str.begin() + root.size())) {
                    result.append(root);
                    f = true;
                    break;
                }
            }
            if (!f)
                result.append(str);
            result.push_back(' ');
        }
        result.pop_back();
        return result;
    }
};
