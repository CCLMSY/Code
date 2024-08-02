#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	long long n,k;
	cin>>n>>k;
	if(k>n/2)k=n-k;
	if(k*2==n)
	{
		cout<<n<<endl;
	}
	else
	{
		long long V=n+n*(k-1);
		long long E=n+n*(2*(k-1)+1);
		cout<<E-V+1<<endl;
	}
	return 0;
}

