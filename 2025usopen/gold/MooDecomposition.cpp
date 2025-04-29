#include<bits/stdc++.h>
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
#define sz(x) (int)((x).size())
#define int long long
using namespace std;
const int mod=1e9+7,mxn=1e6,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,d,q,T;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
int fac[mxn+10],L;
int pow(int x,int ex){
	int ans=1;
	while(ex){
		if(ex&1)ans=(ans*x)%mod;
		x=(x*x)%mod;
		ex>>=1;
	}
	return ans;
}
int inv(int x){
	return pow(x,mod-2);
}
int choose(int n,int r){
	if(n<r)return 0;
	return (fac[n]*inv((fac[n-r]*fac[r])%mod))%mod;
}
int pref[mxn+10],v[mxn+10];
int nxt[mxn+10];
int32_t main(){
	fastio
	cin>>k>>n>>L;
	string a;cin>>a;
	fac[0]=1;
	for(int i=1;i<=mxn;i++)fac[i]=(fac[i-1]*i)%mod;
	for(int i=0;i<n;i++)if(a[i]=='M')v[i+1]++;
	for(int i=1;i<=n;i++)pref[i]=(pref[i-1]+v[i]);
	int ans=1,co=0;
	for(int i=n;i>=1;i--){
		if(v[i]){
			if(co<k)assert(0);
			ans=(ans*choose(co,k))%mod;
			co-=k;
		}
		else co++;
	}
	if(co)assert(0);
	ans=pow(ans,L);
	cout<<ans;
}