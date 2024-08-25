#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char,int> mp1,mp2;
        for(auto c:ransomNote) mp1[c]++;
        for(auto c:magazine) mp2[c]++;
        for(auto [c,cnt]:mp1) if(mp2[c]<cnt) return false;
        return true;
    }
};
int main(){
    Solution sol;
    return 0;
}