#include <iostream>
#include <vector>
#include <limits.h> // 添加这行

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int minLength = INT_MAX;
        int currentSum = 0;

        for (int right = 0; right < nums.size(); right++) {
            currentSum += nums[right];

            while (currentSum >= target) {
                minLength = min(minLength, right - left + 1);
                currentSum -= nums[left];
                left++;
            }
        }

        return (minLength != INT_MAX) ? minLength : 0;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {2, 3, 1, 2, 4, 3};
    int target = 7;

    int result = solution.minSubArrayLen(target, nums);

    cout << "Minimum length of subarray with sum >= " << target << ": " << result << endl;

    return 0;
}
