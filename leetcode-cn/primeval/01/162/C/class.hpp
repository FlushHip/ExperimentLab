// TAG : 爬坡法 + 二分
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = (int)nums.size(), ans = -1;
        for (int l = 0, r = n - 1; l <= r; ) {
            if (r - l + 1 == 1) {
                ans = l;
                break;
            }
            if (r - l + 1 == 2) {
                ans = nums[l] < nums[r] ? r : l;
                break;
            }
            int mid = (l + r) / 2;
            if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
                ans = mid;
                break;
            }
            if (nums[mid] > nums[mid - 1]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
