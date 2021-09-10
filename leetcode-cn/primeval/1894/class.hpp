class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        std::vector<long long> sum(chalk.size());
        sum[0] = chalk[0];
        for (int i = 1; i < (int)chalk.size(); ++i) {
            sum[i] = sum[i - 1] + chalk[i];
        }
        k %= sum.back();
        return std::upper_bound(sum.begin(), sum.end(), k) - sum.begin();
    }
};
