#include<bits/stdc++.h>
using namespace std;

constexpr double eps=1e-6;

void Print_msg(){
    vector<string> msg={
        "选择计算模式：",
        "0. 全部",
        "1. 样本均值X_bar",
        "2. 样本方差S^2",
        "3. 样本标准差S"
    };
    for(auto i:msg) cout<<i<<endl;
}

vector<double> Data;
double X_bar,S2,S;

void Input(){
    cout << "请输入数据集（以非数字结束）：" << endl;
    double x;
    while(true){
        cin>>x;
        if(cin.fail()) break;
        Data.push_back(x);
    }
}

void Cal_X_bar(){
    double sum=0;
    for(auto i:Data) sum+=i;
    X_bar=sum/Data.size();
    cout << "样本均值\tX_bar\t" << X_bar << endl;
}

void Cal_S2(){
    double sum=0;
    for(auto i:Data) sum+=(i-X_bar)*(i-X_bar);
    S2=sum/(Data.size()-1);
    cout << "样本方差\tS^2\t" << S2 << endl;
}

void Cal_S(){
    double sum=0;
    for(auto i:Data) sum+=(i-X_bar)*(i-X_bar);
    S=sqrt(sum/(Data.size()-1));
    cout << "样本标准差\tS\t" << S << endl;
}

void Cal_All(){
    Cal_X_bar();
    Cal_S2();
    Cal_S();
}

int main(){
    Input();
    Cal_All();
    return 0;
}