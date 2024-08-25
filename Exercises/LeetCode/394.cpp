#include<bits/stdc++.h> 
using namespace std;
class Solution {
public:
    string decodeString(string s) {
        string res="",num="";
        int len=s.length(),posl,cntl=0;
        for(int i=0;i<len;i++){
            if(s[i]=='['){
                if(cntl==0) posl=i;
                cntl++;
            }else if(s[i]==']'){
                cntl--;
                if(cntl==0){
                    string dec=decodeString(s.substr(posl+1,i-posl-1));
                    int numi;
                    if(num=="") numi=1; else numi=stoi(num);
                    for(int j=0;j<numi;j++) res+=dec;
                    num="";
                }
            }else if(cntl==0){
                if(s[i]>='0'&&s[i]<='9') num+=s[i];
                else res+=s[i];
            }
        }return res;
    }
};
int main(){
    Solution sol;
    return 0;
}