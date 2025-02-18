#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<cassert>
#include<unordered_map>
#include <queue>
#include <cstdint>
#include<cstring>
#include<limits.h>
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric>
#include<complex>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define s second
#define pii pair<int,int>
#define ppii pair<int,pii>
#define vi vector<int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-lopps")
#define int long long
#define double long double
using namespace std;
using cd = complex<double>;
double const PI=acos(-1);
const int mod=1e9+7,mxn=2e6+5,inf=1e9,minf=-1e9,lg=30;
//#undef int
int k,m,n;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
struct FFT{
	/*
	slow ver. (recursive)
	void fft(vector<cd>&a,bool inv){
		int n=a.size();
		if(n==1)return;
		vector<cd>l,r;
		for(int i=0;i<n;i++){
			if(!(i%2))l.pb(a[i]);
			else r.pb(a[i]);
		}
		fft(l,inv);
		fft(r,inv);
		double ang=2*PI/n*(inv?-1:1);
		cd w(1),wn(cos(ang),sin(ang));
		for(int i=0;i<n/2;i++){
			a[i]=l[i]+w*r[i];
			a[i+n/2]=l[i]-w*r[i];
			if(inv){
				a[i]/=2;
				a[i+n/2]/=2;
			}
			w*=wn;
		}
	}*/
	void fft(vector<cd> & a, bool invert) {
		int n = a.size();

		for (int i = 1, j = 0; i < n; i++) {
			int bit = n >> 1;
			for (; j & bit; bit >>= 1)
				j ^= bit;
			j ^= bit;

			if (i < j)
				swap(a[i], a[j]);
		}

		for (int len = 2; len <= n; len <<= 1) {
			double ang = 2 * PI / len * (invert ? -1 : 1);
			cd wlen(cos(ang), sin(ang));
			for (int i = 0; i < n; i += len) {
				cd w(1);
				for (int j = 0; j < len / 2; j++) {
					cd u = a[i+j], v = a[i+j+len/2] * w;
					a[i+j] = u + v;
					a[i+j+len/2] = u - v;
					w *= wlen;
				}
			}
		}

		if (invert) {
			for (cd & x : a)
				x /= n;
		}
	}
	vector<int>mul(vector<int>a,vector<int>b){
		int n=1;
		vector<cd>fa(all(a)),fb(all(b));
		while(n<a.size()+b.size())n<<=1;
		fa.resize(n);
		fb.resize(n);
		fft(fa,false);
		fft(fb,false);
		//chaning to point value and evaluating
		for(int i=0;i<n;i++)fa[i]*=fb[i];
		//point value to coeff
		fft(fa,true);
		vector<int>result(n);
		for(int i=0;i<n;i++)result[i]=round(fa[i].real());
		return result;
	}
}t;
void solve(){
	cin>>n;
	vector<int>a(n);
	int mx=0;
	for(int i=0;i<n;i++)cin>>a[i],mx=max(mx,a[i]);
	vector<int>v(mx+1,0);
	for(auto i:a)v[i]++;
	vector<int>conv=t.mul(v,v);
	int ans=0;
	for(auto i:a)ans+=(conv[2*i]-1)/2;
	cout<<ans<<'\n';
}
int32_t main(){
	fastio
	solve();
}
/*
*/
