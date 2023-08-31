# 0. 数组的理论
1. **数组基本概念**：
   - 数组是一种线性数据结构，用于存储相同类型的元素，这些元素可以通过索引来访问。数组的元素在内存中是连续存储的。
   - 数组的长度是固定的，一旦创建后，其大小通常不能改变。

2. **数组的访问和操作**：
   - 数组的元素可以通过索引来访问，索引从0开始，最大索引为长度减1。
   - 常见的数组操作包括插入、删除、更新元素等。

3. **数组的时间复杂度**：
   - 数组的读取操作（访问元素）的时间复杂度是O(1)，因为可以直接通过索引定位元素。
   - 数组的插入和删除操作涉及元素的移动，通常情况下需要O(n)的时间复杂度。

4. **双指针技巧**：
   - 在解决数组问题时，双指针是一种常见的技巧。通过使用两个指针来追踪数组的位置，可以在不使用额外空间的情况下进行各种操作，如查找、反转、求和等。
   - 双指针通常用于排序数组、查找目标值、移除元素等场景。

5. **滑动窗口技巧**：
   - 滑动窗口是另一种常见的数组问题解决技巧。通过维护一个窗口范围，可以在线性时间内解决一些复杂的问题，如最小子数组长度、子数组和等。

6. **二分查找技巧**：
   - 对于有序数组，二分查找是一种高效的查找技巧。它可以在O(log n)的时间内找到目标值或确定值的位置。
   - 注意，二分查找只能用于有序数组。

7. **双指针的变种**：
   - 快慢指针：用于寻找链表的中间节点、判断链表是否有环等。
   - 左右指针：用于在有序数组中查找某个范围的值等。

8. **数组问题的分类**：
   - 数组问题可以分为查找类、排序类、旋转类、子数组问题、滑动窗口问题等。
   - 每类问题都有其特定的解题思路和技巧。

9. **空间与时间权衡**：
   - 在解决数组问题时，有时可以通过牺牲一些额外的空间来换取更快的时间复杂度。
   - 例如，可以使用哈希表来进行快速的查找操作，但会消耗额外的空间。

10. **问题建模**：
    - 在解决数组问题时，将问题抽象成具体的模型有助于更好地思考解决方案。例如，最小子数组长度问题可以用滑动窗口来建模。

总之，数组问题在算法题目中占据了重要的地位，掌握数组的基本概念和常见的解题技巧，以及在具体问题中应用这些技巧，可以帮助你更有效地解决各种数组问题。通过不断练习和思考，你将能够更加熟练地处理各种不同类型的数组问题。

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

## 1.1 第二种写法
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        int left = 0;
        int right = size;
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
```
**(left < right)**

这种写法的核心就是right直接等于size, 最后不会出现left == right 的情况，就是一个数计算。

### ex1: 12

当使用 `while (left < right)` 循环条件查找目标值 `12` 时，以下是每一轮循环的过程：

初始状态：`left = 0`, `right = 6`, `mid = (0 + 6) / 2 = 3`, `nums[mid] = 5`

1. 第一轮：`5` 小于 `12`，所以目标值 `12` 可能在右半部分，更新 `left = mid + 1 = 4`

   新的状态：`left = 4`, `right = 6`, `mid = (4 + 6) / 2 = 5`, `nums[mid] = 12`


### ex2: 9 (这个案例是看 right = mid )
当使用 `while (left < right)` 循环条件查找目标值 `9` 时，以下是每一轮循环的过程：

初始状态：`left = 0`, `right = 6`, `mid = (0 + 6) / 2 = 3`, `nums[mid] = 5`

1. 第一轮：`5` 小于 `9`，所以目标值 `9` 可能在右半部分，更新 `left = mid + 1 = 4`

   新的状态：`left = 4`, `right = 6`, `mid = (4 + 6) / 2 = 5`, `nums[mid] = 12`

2. 第二轮：`12` 大于 `9`，所以目标值 `9` 可能在左半部分，更新 `right = mid = 5`

   新的状态：`left = 4`, `right = 5`, `mid = (4 + 5) / 2 = 4`, `nums[mid] = 9`


# 2. 移除元素法
这个题不要使用额外的数组空间，不需要考虑数组中超出新长度后面的元素，所以可以理解为数组还是那么长，只是前面的值变了，把那些不要的扔掉剩下的往前移动了。

## 2.1 暴力解法
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



## 2.2 双指针法
如果快指针指到了不是val的元素，快指针继续往前走，慢指针留在这个元素等待快指针找到下一个不是val的，然后慢指针用来赋值当前的，前面第一个nums[slow] == nums fast 可以理解为是nums[0] == nums[0],慢指针先赋值再往前走。

因为慢指针负责把数组往前挪，所以这个慢指针就是最后的size

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
给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。

示例 1：

- 输入：nums = [-4,-1,0,3,10]
- 输出：[0,1,9,16,100]
- 解释：平方后，数组变为 [16,1,0,9,100]，排序后，数组变为 [0,1,9,16,100]

## 3.1 暴力做法
这种做法其实比较通用的，就是无论什么组合的数组都是可以用到的，因为用了sort(), 但是并没有用到题目说了是非递减的顺序，这里其实也可以用到双指针的写法去做
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

## 3.2 双指针写法
既然是非递减的数组，那么最大的平方值应该是出现在数组的左右两边，这样的话每次比较左右两边就可以了，这里判断的else其实包含了abs(A[left]) == abs(A[right])的情况，这里其实左右指针往中间走一步都是一样的，这里重要的是result数组要遍历完数组A的全部 

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

# 4. 长度最小的子数组
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。

示例：

- 输入：s = 7, nums = [2,3,1,2,4,3]
- 输出：2
- 解释：子数组 [4,3] 是该条件下的长度最小的子数组。

## 4.1 题解(滑窗法)
这里其实用的是滑窗法，但是我觉得也是一种双指针的写法，快指针往前走，一旦达到了相加等于target的值就停下，然后慢指针也走，然后快指针继续走到加起来等于target的地方。

易错的点是sum的计算，每一次慢指针移动的时候，都需要重置一次sum, 这里就是滑窗法的特点，直接每次滑的时候把滑的扔掉，这样就不用通过快慢指针的区间写一个for循环了，效率是比较高的。 

第二个易错点是题目需要返回的是长度，举个例子，如果是第2,3索引刚好满足，那么长度就应该是 3 - 2 + 1 = 2, 这里没有+1的话是不准确的

```cpp
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
```