/*差分数组：用于快速修改数组中的元素

原理：对数组中 [left, right] 数据进行相同的修改时，可转化为对差分数组 left, right + 1 两个元素的修改

原理解析：假设存在数组 arr = [3, 5, 8, 8, 10]
对应差分数组 diff = [3, 2, 3, 0, 2] (即diff[0] = arr[0], diff[i] = arr[i] - arr[i - 1])
这表明，差分数组可以轻易的还原为原数组，即 arr[0] = diff[0], arr[i] = diff[i] + diff[i - 1] + ...
此时，如果对 arr 的 [1, 3] 的元素都加 10， 即 arr' = [3, 15, 18, 18, 10]
对应 diff' = [3, 12, 3, 0, -8], 也就是对 diff 的 1 元素 +10， 4 元素 -10
这样就实现了对区间内数据的统一更改。

适用情景：对区间内数据统一修改，并判断修改时元素是否符合特定条件。例如：被覆盖元素个数，列车上下车， 连续区间合并...

二维差分数组： d[i][j] = a[i][j] - a[i - 1][j] - a[i][j - 1] + a[i][j]
a[i][j] = 求和d[x][y](x <= i, y <= j);
d[i][j] 表示 从 (i, j) 这个点开始， 右下方矩形所有元素都有 d[i][j] 的增量
因此，如果对 a[i1][j1] —— a[i2][j2] 的所有元素增加 k , 相当于在 d 上修改：
-> d[i1][j1] += k; d[i1][j2 + 1] -= k; d[i2 + 1][j1] -= k; d[i2 + 1][j2 + 1] += k(多减的部分加回来)
再通过对二维数组的前缀和求和，得到更改后的新矩阵的各个元素。

差分与前缀和， 就像导数与原函数。 导数到原函数需要积分， 差分数组到原数组需要累加求前缀和。
*/

//leetcode 2848 

#include"headfile.h"

class difference_array {
public: 
    int numberOfPoints(vector<vector<int>>& nums) {
        int max_end = ranges::max(nums, {}, [](const auto& a) { return a[1]; })[1]; //确认数组范围
        vector<int> diff(max_end + 2); //建立并定义差分数组
        for (auto &ele : nums) {
            diff[ele[0]]++;
            diff[ele[1]+1]--;
        }
        int ans = 0, s = 0;
        for (int d : diff) { //由差分数组还原原数组各个元素，并判断是否符合要求
            s += d;
            ans += s > 0;
        }
        return ans;
    }
};

//leetcode 56 差分数组合并区间

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int max_end = ranges::max(intervals, {}, [](const auto& a) { return a[1]; })[1]; //获取差分数组的最大范围
        vector<vector<int>> ans;
        int n = intervals.size();
        vector<int> diff(max_end * 2 + 2);//注意区间范围，离散后的差分数组最大为 max_end * 2 + 1
        for (auto & i : intervals) {
            int l = i[0] * 2; //离散化数组，例如[1, 4],[5, 8]不离散的话会合并为一个区间[1, 8]，但实际上4, 5不相交。
            int r = i[1] * 2; //这其实是一个由点到线的过程，把原本相邻的点（实际不合并）通过“*2离散”来分开
            diff[l]++;
            diff[r + 1]--;
        }
        int left = 0, right = 0, sum = 0, flag = 0;
        for(int i = 0; i <= max_end * 2 + 1; i++) {
            sum += diff[i]; //遍历差分数组：sum 由 0 变为正数是得到左端点， 从正数变为 0 是得到右端点的后一位
            if (sum >= 1 && flag == 0) {
                flag = 1;
                left = i;
            }
            if (flag == 1 && sum == 0 || i == max_end * 2 + 1 && flag == 1) {
                flag = 0;
                right = i - 1;
                ans.push_back({left / 2, right / 2}); //还原原数
            }
        }
        return ans;
    }
};