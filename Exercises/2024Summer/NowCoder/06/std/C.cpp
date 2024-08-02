#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1.);
typedef double db;
struct point
{
	db x,y;
	point operator+(const point &p)const{return {x+p.x,y+p.y};}
	point operator-(const point &p)const{return {x-p.x,y-p.y};}
	db operator*(const point &p)const{return x*p.y-y*p.x;}
	db operator^(const point &p)const{return x*p.x+y*p.y;}
	point turn90()const{return (point){-y,x};}
	db abs2()const{return x*x+y*y;}
	friend istream& operator>>(istream &is,point &p){is>>p.x>>p.y;return is;}
	friend ostream& operator<<(ostream &os,const point &p){os<<p.x<<' '<<p.y;return os;}
	point turn(db k1)const{return (point){x*cos(k1)-y*sin(k1),x*sin(k1)+y*cos(k1)};}
	point operator*(const db k1)const{return {x*k1,y*k1};}
	point operator/(const db k1)const{return {x/k1,y/k1};}
	db dis(const point &k1)const{return ((*this)-k1).abs();}
	db abs()const{return hypot(x,y);}
	point unit()const{db w=abs();return (point){x/w,y/w};}
};
int main()
{
	ios_base::sync_with_stdio(false);
	cout<<fixed<<setprecision(12);
	int n,k;
	cin>>n>>k;
	if(k>=4)cout<<"NO"<<endl;
	else if(k%2==1 and n%2==1)cout<<"NO"<<endl;
	else if(k==1)
	{
		cout<<"YES"<<endl;
		for(int i=0;i<n/2;i++)
		{
			cout<<i*2.<<' '<<0.<<endl;
			cout<<i*2.<<' '<<1.<<endl;
		}
	}
	else if(k==2)
	{
		cout<<"YES"<<endl;
		double R=1./(2.*sin(pi/n));
		for(int i=0;i<n;i++)
		{
			cout<<R*cos(2*i*pi/n)<<' '<<R*sin(2*i*pi/n)<<endl;
		}
	}
	else
	{
		if(n<=14)cout<<"NO"<<endl;
		else
		{
			auto solve=[&](const vector<double> &len)
			{
				double sum=0,maxx=0;
				for(auto z:len)sum+=z,maxx=max(maxx,z);
				auto chk=[&](double R)
				{
					double t=0;
					for(auto z:len)
						t+=2*asin(z/2/R);
					return t;
				};
				double l=maxx/2.,r=sum;
				for(int tt=1;tt<=100;tt++)
				{
					double mid=(l+r)/2.;
					if(chk(mid)>2*pi)l=mid;
					else r=mid;
				}
				vector<point> ret;
				double R=(l+r)/2;
				double t=0;
				for(auto z:len)
				{
					t+=2*asin(z/2/R);
					ret.emplace_back(R*cos(t),R*sin(t));
				}
				cerr<<"! "<<R<<' '<<t<<endl;
				return ret;
			};
			if(n%4==0)
			{
				cout<<"YES"<<endl;
				vector<double> len;
				for(int i=1;i<=n/4;i++)
				{
					len.push_back(1);
					len.push_back(sqrt(3));
				}
				auto pts=solve(len);
				for(int i=0;i<n/2;i+=2)
				{
					point A=pts[i],B=pts[i+1];
					point mid=(A+B)/2,delx=(B-mid).unit(),dely=delx.turn90();
					point C=mid+dely/2,D=mid-dely/2;
					cout<<A<<endl<<C<<endl<<D<<endl<<B<<endl;
				}
			}
			else
			{
				cout<<"YES"<<endl;
				vector<double> len;
				len.push_back(1.);
				len.push_back(sqrt(3.)+1);
				for(int i=2;i<=n/4;i++)
				{
					len.push_back(1.);
					len.push_back(sqrt(3.));
				}
				auto pts=solve(len);
				{
					point A=pts[0],B=pts[1];
					point mid=(A+B)/2,delx=(B-mid).unit(),dely=delx.turn90();
					point C=mid+dely/2-delx/2,D=mid-dely/2-delx/2;
					point E=mid+dely/2+delx/2,F=mid-dely/2+delx/2;
					cout<<A<<endl<<C<<endl<<D<<endl<<E<<endl<<F<<endl<<B<<endl;
				}
				for(int i=2;i<(n-1)/2;i+=2)
				{
					point A=pts[i],B=pts[i+1];
					point mid=(A+B)/2,delx=(B-mid).unit(),dely=delx.turn90();
					point C=mid+dely/2,D=mid-dely/2;
					cout<<A<<endl<<C<<endl<<D<<endl<<B<<endl;
				}
			}
		}
	}
	
	return 0;
}
