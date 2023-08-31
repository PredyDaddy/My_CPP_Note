#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        int left = 0;
        int right = size;  // 这里不是size - 1了
        while (left < right){
            int mid = (left + right) / 2;
            if (nums[mid] == target){
                return mid;
            }
            else if (nums[mid] > target){
                right = mid;
            } 
            else {
                left += 1;
            }
        }
        return -1;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int target = 9;

    int result = solution.search(nums, target);

    if (result != -1) { 
        cout << "Target " << target << " found at index " << result << endl;
    } else {
        cout << "Target " << target << " not found in the array" << endl;
    }

    return 0;
}
