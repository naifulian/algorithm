/* 问题描述
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target  的那两个整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。你可以按任意顺序返回答案

2 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
只会存在一个有效答案
*/

/* 
1. 每种输入只会对应一个答案，说明题目保证只有一个解
2. 不能使用两次相同的元素 -> 不能使用同一个元素两次
3. 可以按照任意顺序返回答案
4. 返回的是数组下标，如果使用快速排序就需要保存原来的数组下标
*/

/* 解法
这道题是一个排列组合的数学问题，找出数组一个元素个数为 2 的子集，使得整个子集的两个元素和与目标值相等
1.暴力：使用双层 for 循环暴力遍历所有可能的组合，检查他们的和是否为目标值。

2.排序 + 头尾指针遍历：将原数组进行排序，然后利用排序好的数组是单调递增的这个性质来调整头尾指针，使得可以更高效的缩小搜索范围，排序一般使用
快速排序，时间复杂度 O(nlogn)，但是快速排序是不稳定的排序，会打乱数组的下标，而题目要求返回的是原来的数组下标，所以需要一种手段保存原始数组
的下标。
    1.如果当前头尾指针指向的元素和小于 target，则说明需要更大的数，因此调整头指针
    2.如果当前头尾指针指向的元素和大于 target，则说明需要更小的数，因此调整尾指针

3.哈希：时间换空间，将组合问题转换为查找问题，一次 for 循环就能得到答案。利用哈希表存储已经遍历过的元素和对应的下标，计算当前遍历到的数对于
target 的补数，然后查找该补数是否在哈希表中，如果在说明找到了解，如果不在，则将 nums[i] 和其下标 i 存入哈希表
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

// 输入的整数数组 num
vector<int> nums(10000);
// 目标值
int target;

namespace S1 {
// 暴力，时间复杂度 O(n^2)，空间复杂度 O(1)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if(nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        // 由于题目保证一种输入只会对应一个答案，所以不会从这里返回
        return {};
    }
};
}

namespace S2 {
// 排序 + 头尾指针，时间复杂度 O(nlogn)，空间复杂度 O(n)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 保存数组下标和值的关系到 pair 中
        vector<pair<int, int>> idx2nums;
        for (int i = 0; i < nums.size(); ++i) {
            idx2nums.emplace_back(nums[i], i);
        }
        // 根据数组的值进行排序
        sort(idx2nums.begin(), idx2nums.end());

        // 头尾指针遍历
        int head = 0, tail = nums.size() - 1;
        while(head < tail) {
            int sum = idx2nums[head].first + idx2nums[tail].first;
            if(sum == target) {
                return {idx2nums[head].second, idx2nums[tail].second};
            } else if (sum < target) {
                head++;
            } else {
                tail--;
            }
        }
        return {};
    }
};
}

namespace S3 {
// 哈希，最优解
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 哈希表
        unordered_map<int, int> idx2num;
        for (int i = 0; i < nums.size(); ++i) {
            // 当前元素相对于 target 的补数
            int complements = target - nums[i];
            // 在哈希表中找到了当前元素的补数
            if(idx2num.find(complements) != idx2num.end()) {
                return {idx2num[complements], i};
            }
            // 在哈希表中没有找到当前元素的补数，则将该元素加入到哈希表
            idx2num[nums[i]] = i;
        }
        return {};
    }
};
}


ostream& operator<<(ostream& os, const vector<int>& nums) {
    os << nums[0] << " " << nums[1] << endl;
    return os;
}



void test(vector<int> nums, int target) {
    S1::Solution s1;
    cout << s1.twoSum(nums, target) << endl;
    S2::Solution s2;
    cout << s2.twoSum(nums, target) << endl;
    S3::Solution s3;
    cout << s3.twoSum(nums, target) << endl;
}

#define TEST 4
int main() {

#if TEST == 1 || TEST == 4
    // TEST1：应该返回 [0, 1]
    nums = {2, 7, 11, 15};
    target = 9;
    cout << "==========TEST1==========" << endl;
    cout << "       应该返回 0 1       " << endl;
    test(nums, target);
    
#endif

    // TEST2：应该返回 [1, 2]
#if TEST == 2 || TEST == 4
    nums = {3, 2, 4};
    target = 6;
    cout << "==========TEST2==========" << endl;
    cout << "       应该返回 1 2      " << endl;
    test(nums, target);
#endif
    // TEST3：应该返回 [0, 1]
#if TEST == 3 || TEST == 4
    nums = {3, 3};
    target = 6;
    cout << "==========TEST3==========" << endl;
    cout << "       应该返回 0 1       " << endl;
    test(nums, target);
#endif
    return 0;
}