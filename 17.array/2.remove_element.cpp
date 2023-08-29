#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        int size = nums.size();
        for (int fast = 0; fast < size; fast++){
            if (nums[fast] != val){
                // 这个时候快指针指向不是val但是前面是val, 慢指针留在了这个val的区间
                nums[slow] = nums[fast];
                slow++;  // 赋值完慢指针完成任务就往前走
            }
        }
        return slow; 
    }
};

int main() {
    Solution solution;
    vector<int> nums = {3, 2, 2, 3, 4, 5, 3, 6};
    int size = nums.size();
    int val = 2;

    int newLength = solution.removeElement(nums, val);

    cout << "New length of the array: " << newLength << endl;
    cout << "Modified array: ";
    for (int i = 0; i < newLength; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;

    cout << "actual array is: ";
    for (int i = 0; i < size; i++){
        cout << nums[i] << " ";
    }
    cout<< endl;
    return 0;
}
