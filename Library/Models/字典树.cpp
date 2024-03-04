#include<bits/stdc++.h>
using namespace std;
struct TRIE{
    TRIE* next[26];
    int cnt, end;
    TRIE(){
        cnt = end = 0;
        for(int i=0;i<26;i++) next[i] = NULL;
    }
    void insert(string s){
        TRIE* p = this;
        for(auto& c:s) {
            if(p->next[c-'a']==NULL) p->next[c-'a'] = new TRIE();
            p = p->next[c-'a'];
            p->cnt++;
        }
        p->end++;
    }   
    int count(string s){
        TRIE* p = this;
        for(auto& c:s) {
            if(p->next[c-'a']==NULL) return 0;
            p = p->next[c-'a'];
        }
        return p->end;//返回s的个数
        // return p->cnt;//返回s的前缀个数
    }
};