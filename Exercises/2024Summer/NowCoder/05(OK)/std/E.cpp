#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
int a[N],b[N];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int ans = 0;
        int sum = 0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            cin>>b[i];
            if(b[i]<a[i])ans++;
            else if(b[i]==a[i])sum++;
        }
        cout<<ans+(sum+1)/2<<"\n";
    }
}