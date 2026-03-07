/*差分数组：用于快速修改数组中的元素

原理：对数组中 [left, right] 数据进行相同的修改时，可转化为对差分数组 left, right + 1 两个元素的修改

原理解析：假设存在数组 arr = [3, 5, 8, 8, 10]
对应差分数组 diff = [3, 2, 3, 0, 2] (即diff[0] = arr[0], diff[i] = arr[i] - arr[i - 1])
这表明，差分数组可以轻易的还原为原数组，即 arr[0] = diff[0], arr[i] = diff[i] + diff[i - 1] + ...
此时，如果对 arr 的 [1, 3] 的元素都加 10， 即 arr' = [3, 15, 18, 18, 10]
对应 diff' = [3, 12, 3, 0, -8], 也就是对 diff 的 1 元素 +10， 4 元素 -10
这样就实现了对区间内数据的统一更改。

适用情景：对区间内数据统一修改，并判断修改时元素是否符合特定条件。例如：被覆盖元素个数，列车上下车...

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