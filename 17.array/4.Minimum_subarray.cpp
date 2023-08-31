#include <iostream>
#include <vector>
#include <limits.h> // 添加这行

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int slow = 0;
        int size = nums.size();
        int min_length = INT_MAX;
        int current_sum = 0;
        for (int fast = 0; fast < size; fast++)
        {
            current_sum += nums[fast];
            while (current_sum >= target){
                min_length = min(min_length, fast - slow + 1);
                current_sum -= nums[slow];   // 当每次慢指针往前走的时候就要把之前的减掉，因为sum计算的是整个区间的，不然的话就要写for循环来遍历了
                slow++;
                
            }
        }
        return (min_length != INT_MAX) ? min_length : 0;
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
