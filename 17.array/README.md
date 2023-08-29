# 1. 二分查找
二分查找法（Binary Search）是一种在**无重复有序**数组中查找特定元素的高效算法。它也被称为折半查找法。该算法的思想是不断地将查找范围缩小为一半，从而快速定位目标元素的位置。

以下是二分查找法的基本步骤：

1. 确定查找范围：在有序数组中，首先确定要查找的范围，一般来说，初始范围为整个数组。

2. 计算中间位置：找到查找范围的中间位置，计算中间位置的索引值。

3. 比较中间元素：将中间位置的元素与目标元素进行比较。

4. 调整范围：根据比较结果，如果中间元素等于目标元素，则查找成功；如果中间元素大于目标元素，则目标元素可能在左半部分，将查找范围缩小为左半部分；如果中间元素小于目标元素，则目标元素可能在右半部分，将查找范围缩小为右半部分。

5. 重复步骤：重复执行步骤 2 到步骤 4，直到找到目标元素或者查找范围缩小为空。

二分查找法的时间复杂度为 O(log n)，其中 n 是数组的长度。相比于线性查找（遍历数组逐个比较），二分查找法的效率要高得多，特别是对于大型有序数组。

需要注意的是，二分查找法要求数组是有序的，如果数组无序，就需要先进行排序操作，然后再进行二分查找。


```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1; 
        while (left <= right){  // 这里一定要小于等于，不然最后一个树没有办法识别了
            int mid = (left + right) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[mid] < target){
                left = mid + 1;                
            }
            else {
                right = mid - 1;
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
```

当你调用 `search` 函数来寻找目标值 `12` 时，`left` 和 `right` 代表着当前搜索的范围。让我们逐轮分析你提供的代码，来看看每一轮循环迭代后的情况。

初始时，`left` 是 0，`right` 是 `nums.size() - 1`，即 5。开始循环：

1. **第一轮循环**：
    - `mid` 计算为 `(0 + 5) / 2 = 2`。
    - `nums[mid] = 3` 不等于 `target`。
    - 由于 `nums[mid]` 小于 `target`，进入 `else if` 分支，将 `left` 更新为 `mid + 1`，即 `left` 变为 3。
    - 现在搜索范围变成了 3 到 5，即 `{5, 9, 12}`。

2. **第二轮循环**：
    - `mid` 计算为 `(3 + 5) / 2 = 4`。
    - `nums[mid] = 9` 不等于 `target`。
    - 由于 `nums[mid]` 小于 `target`，进入 `else if` 分支，将 `left` 更新为 `mid + 1`，即 `left` 变为 5。
    - 现在搜索范围变成了 5 到 5，即 `{12}`。

3. **第三轮循环**：
    - `mid` 计算为 `(5 + 5) / 2 = 5`。
    - `nums[mid] = 12` 等于 `target`，返回 `mid`，即索引 5。
    - 循环结束，目标值 `12` 被找到，函数返回。

综上所述，搜索目标值 `12` 的过程如下：

1. 初始搜索范围：`{-1, 0, 3, 5, 9, 12}`
2. 第一轮迭代后的搜索范围：`{5, 9, 12}`
3. 第二轮迭代后的搜索范围：`{12}`
4. 第三轮迭代找到目标值 `12`，返回索引 5。

最终输出应为 "Target 12 found at index 5"。


4. 如果是13，这里并没有13，最后一次循环之前，left = right = mid = 5, 然后 left = mid + 1 = 5 + 1 = 6, (6 > 5) 跳出了循环，到return -1;  


# 2. 移除元素法
暴力解法
```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size();
        for (int i = 0; i < size; i++){
            if (nums[i] == val){
                // 开始把全部的数组往前移动一位
                for (int j = i + 1; j < size; j++){
                    nums[j - 1] = nums[j];
                }
                i--;
                size--;
            }
        }
        return size;
    }
};
```

双指针法
如果快指针指到了不是val的元素，快指针继续往前走，慢指针留在这个元素等待快指针找到下一个不是val的，然后慢指针用来赋值当前的，前面第一个nums[slow] == nums fast 可以理解为是nums[0] == nums[0],慢指针先赋值再往前走

这里的数值其实是没有被改变的，可以通过下面的代码查看
```cpp
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

```
```bash
(base) root@ubuntu-01:/data/My_CPP_Note/17.array# ./a.out 
New length of the array: 6
Modified array: 3 3 4 5 3 6 
actual array is: 3 3 4 5 3 6 3 6 
```

# 3. 有序数组的平方
暴力做法
```cpp
class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        for (int i = 0; i < A.size(); i++) {
            A[i] *= A[i];
        }
        sort(A.begin(), A.end()); // 快速排序
        return A;
    }
};
```

双指针写法
```cpp
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
        for (int i = size - 1; i >=0; i--){
                if ((A[left] * A[left]) > (A[right] * A[right])) {
                    result[i] = A[left] * A[left];
                    left ++;
                }
                else if ((A[left] * A[left]) < (A[right] * A[right])){
                    result[i] = A[right]* A[right];
                    right--; 
                }
        }
        return result;
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {-4, -1, 0, 3, 10};
    vector<int> nums2 = {-7, -3, 2, 3, 11};

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
```