#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> res(nums.size());
        partial_sum(nums.begin(), nums.end(), res.begin());
        return res;
    }
};
int main(){
    Solution sol;
    vector<int> nums={1,2,3,4};
    auto res=sol.runningSum(nums);
    for(int i=0;i<res.size();i++) cout<<res[i]<<" ";
    return 0;
}