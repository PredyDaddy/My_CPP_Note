#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        int size = A.size();
        vector<int> result(size);
        int left = 0;
        int right = size - 1;
        for (int i = size - 1; i >=0; i--)
        {
            if (abs(A[left]) > abs(A[right])){
                result[i] = A[left] * A[left];
                left++;
            }
            else {
                result[i] = A[right] * A[right];
                right--;
            }
        }
        return result;
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {-4, -1, 0, 3, 10};
    vector<int> nums2 = {-7, -3, 2, 3, 3, 11};

    vector<int> result1 = solution.sortedSquares(nums1);
    vector<int> result2 = solution.sortedSquares(nums2);

    cout << "Sorted squares of nums1: ";
    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Sorted squares of nums2: ";
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}