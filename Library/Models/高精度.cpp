#include<bits/stdc++.h>
using namespace std;

// 高精度整数
struct HAint{
    string val;
    int fl=1;
    HAint(string s="0"){
        assert(s.size());
        if(s[0]=='-') fl=-1,val=s.substr(1);
        else val=s;
    }
    string abs()const{ return val; }
    string str()const{ return (fl==-1?"-":"")+val; }
    friend ostream& operator<<(ostream &os,const HAint &a){ os<<a.str(); return os; }
    friend istream& operator>>(istream &is,HAint &a){ string s; is>>s; a=HAint(s); return is; }
    bool operator<(const HAint &b)const{ // O(n)
        if(fl!=b.fl) return fl<b.fl;
        if(val.size()!=b.val.size()) return val.size()*fl<b.val.size()*b.fl;
        size_t n=val.size(),m=b.val.size();
        size_t ub=min(n,m);
        for(size_t i=0;i<ub;i++){ if(val[n-1-i]!=b.val[m-1-i]) return (val[n-1-i]-'0')*fl<(b.val[m-1-i]-'0')*b.fl; }
        return n<m;
    }
    bool operator>(const HAint &b)const{ return b<*this; }
    bool operator<=(const HAint &b)const{ return !(*this>b); }
    bool operator>=(const HAint &b)const{ return !(*this<b); }
    bool operator==(const HAint &b)const{
        if(fl!=b.fl||val.size()!=b.val.size()) return 0;
        return val==b.val;
    }
    bool operator!=(const HAint &b){ return !(*this==b); }

    HAint operator-()const{
        HAint res=*this;
        res.fl=-res.fl;
        return res;
    }
    HAint operator+(const HAint &b)const{
        if(fl!=b.fl) return *this-(-b);
        string res;
        int i=val.size()-1,j=b.val.size()-1,c=0;
        while(i>=0||j>=0||c){
            if(i>=0) c+=val[i--]-'0';
            if(j>=0) c+=b.val[j--]-'0';
            res.push_back(char(c%10+'0'));
            c/=10;
        }
        if(fl==-1) res.push_back('-');
        reverse(res.begin(),res.end());
        return HAint(res);
    }
    HAint operator-(const HAint &b)const{
        if(fl!=b.fl) return *this+(-b);
        if(fl==-1) return (-b)-(-*this);
        if(*this<b) return -(b-*this);
        string res;
        int i=val.size()-1,j=b.val.size()-1,c=0;
        while(i>=0||j>=0||c){
            if(i>=0) c+=val[i--]-'0';
            if(j>=0) c-=b.val[j--]-'0';
            if(c<0) res.push_back(char(c+10+'0')),c=-1;
            else res.push_back(char(c+'0')),c=0;
        }
        while(res.size()>1&&res.back()=='0') res.pop_back();
        reverse(res.begin(),res.end());
        return HAint(res);
    }
};
int main(){
    HAint a,b;
    cin>>a>>b;
    return 0;
}