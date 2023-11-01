#include<bits/stdc++.h>
using namespace std;
int main(){
    srand(time(0));
    int x=rand()%101;//目标数
    int ub=100,lb=0;//上下界
    int guess;
    while(1){
        cin >> guess;
        if(guess==x){//猜中
            cout << "Good Job!" << endl;
            break;
        }else if(guess<x){//猜小了
            cout << "Too Small!" << endl;
            lb=max(lb,guess);
            cout << "Range:" << '[' <<lb << ',' << ub << ']' << endl;
        }else{//猜大了
            cout << "Too Large!" << endl;
            ub=min(ub,guess);
            cout << "Range:" << '[' <<lb << ',' << ub << ']' << endl;
        }
    }
    return 0;
}//Powered by CC