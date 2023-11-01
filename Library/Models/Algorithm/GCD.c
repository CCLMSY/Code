//GCD:最大公约数
#include<stdio.h>
//辗转相除法 时间复杂度：O（logn）
long long GCD(long long a,long long b)
{
    long long m;
    while(a%b) {m=a%b;a=b;b=m;}
    //若a<b 则等价于a、b互换；若a>b,则进行辗转相除
    return b;
}
//辗转相除法+递归
long long GCD(long long a,long long b)
{
    return b==0?a:GCD(b,a%b);
    //b的位置是递归后余数的位置 若余数为0则a的位置为最大公约数
}
int main()
{
    printf("%lld",GCD(375,500));
}