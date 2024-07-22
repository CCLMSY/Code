#include<bits/stdc++.h>

using namespace std;

void solve(){
  string s;
  cin>>s;
  string cur="";

  int i=0;
  int c=0;
  while(i<(int)s.size()){
    if(s.substr(i,1) == "/") {
      if((c<2) || (c>=2 && cur.find('=') != -1))
        cout<<cur<<"\n";
      cur.clear();
      i++;
      c++;
    }else if(s.substr(i,3) == "://") {
      if((c<2) || (c>=2 && cur.find('=') != -1))
        cout<<cur<<"\n";
      cur.clear();
      i+=3;
      c++;
    }else{
      cur+=s[i];
      i++;
    }
  }
}
int main(){
  int t;
  cin>>t;
  while(t--)solve();
}