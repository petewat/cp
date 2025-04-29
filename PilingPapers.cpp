#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<limits.h>
#include <cassert>
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric> //gcd(a,b)
#include<bitset>
#define ll long long
#define f first
#define endl "\n"
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
#pragma GCC optimize ("03,unroll-loops")
using namespace std;
#define int long long
#define double long double
const int mxn=303,inf=1e18+1,minf=-1e9,mod=1e9+7;
int n,A,B;
int dp[3][3][20][20];
//0 more, 1 less ,2 =
int v[mxn+10];
vector<int>NA,NB;
void add(int &x,int y){
	x=(x+y+mod)%mod;
}
int getlower(int sz){
	int ans=0;
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int k=0;k<=sz;k++){
		if(i==0&&j==1)add(ans,dp[i][j][k][sz-k]);
		if(i==1&&j!=0)add(ans,dp[i][j][k][sz-k]);
		if(i==2&&j!=0)add(ans,dp[i][j][k][sz-k]);
	}	
	return ans;
}
int gethigher(int sz){
	int ans=0;
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int k=0;k<=sz;k++){
		if(i==0&&j!=1)add(ans,dp[i][j][k][sz-k]);
		if(i==1&&j==0)add(ans,dp[i][j][k][sz-k]);
		if(i==2&&j!=1)add(ans,dp[i][j][k][sz-k]);
	}
	return ans;
}
vector<int>go[mxn+10];
vector<int> getdig(int x){
	vector<int>ans;
	while(x){
		ans.pb(x%10);
		x/=10;
	}
	reverse(all(ans));
	return ans;
}

int p[mxn+10],fac[mxn+10];
int inv(int x){
	int ans=1,ex=mod-2;
	while(ex){
		if(ex&1)ans=(ans*x)%mod;
		x=(x*x)%mod;
		ex>>=1;
	}
	return ans;
}
int choose(int N,int R){
	if(N-R<0)return 0;
	return (fac[N]*inv((fac[R]*fac[N-R])%mod))%mod;
}
int ra[mxn+10][mxn+10];
int keep[mxn+10][mxn+10],keep2[mxn+10][mxn+10];
void getDp(int l,int r,vector<int>X,int g,int mul){
	int cdp[3][3][20][20];
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int k=0;k<=X.size();k++)for(int g=0;g<=X.size();g++)cdp[i][j][k][g]=dp[i][j][k][g]=0;
	dp[2][2][0][0]=1;
	for(int i=r;i>=l;i--){
		for(int forward=0;forward<=X.size();forward++)for(int backward=0;backward+forward<=X.size();backward++){
			for(int j=0;j<3;j++)for(int k=0;k<3;k++){
				//not choose
				add(cdp[j][k][forward][backward],dp[j][k][forward][backward]);
				//choose
				if(k!=2)add(cdp[j][k][forward+1][backward],dp[j][k][forward][backward]);
				else{
					if(v[i]>X[forward])add(cdp[j][0][forward+1][backward],dp[j][k][forward][backward]);
					if(v[i]<X[forward])add(cdp[j][1][forward+1][backward],dp[j][k][forward][backward]);
					if(v[i]==X[forward])add(cdp[j][2][forward+1][backward],dp[j][k][forward][backward]);
				}
				if(v[i]>X[X.size()-1-backward])add(cdp[0][k][forward][backward+1],dp[j][k][forward][backward]);
				else if(v[i]<X[X.size()-1-backward])add(cdp[1][k][forward][backward+1],dp[j][k][forward][backward]);
				else if(v[i]==X[X.size()-1-backward])add(cdp[j][k][forward][backward+1],dp[j][k][forward][backward]);
				dp[j][k][forward][backward]=0;
			}
		}
		swap(cdp,dp);
		if(g)add(keep[i][r],mul*getlower(X.size()));
		else add(keep[i][r],mul*gethigher(X.size()));
	}	
}
int32_t main(){
	fastio
	cin>>n>>A>>B;
	p[0]=fac[0]=1;
	for(int i=1;i<=n;i++)cin>>v[i],p[i]=(p[i-1]*2LL)%mod,fac[i]=(fac[i-1]*i)%mod;
	vector<int>NA=getdig(A),NB=getdig(B);
	int yes=0;
	if(NA.size()==NB.size()){
		yes=1;
		NA=getdig(A-1);
	}
	int q;cin>>q;
	vector<pair<pii,int>>qry(q);
	for(int i=0;i<q;i++){
		cin>>qry[i].f.f>>qry[i].f.s,qry[i].s=i;
		go[qry[i].f.s].pb(qry[i].f.f);
	}
	for(int r=1;r<=n;r++){
		if(go[r].empty())continue;
		sort(all(go[r]));
		if(yes){
			getDp(go[r][0],r,NB,1,1);//NA lower
			getDp(go[r][0],r,NA,1,-1);//NB lower
		}
		else{
			getDp(go[r][0],r,NA,0,1);//NB higher
			getDp(go[r][0],r,NB,1,1);//NA lower
		}
	}
	for(int i=0;i<q;i++){
		int l,r;
		l=qry[i].f.f,r=qry[i].f.s;
		int ans=0;
		if(yes)ans=keep[l][r];
		else{
			for(int i=NA.size()+1;i<NB.size();i++){
				//r-l+1 choose i *(2^i)
				add(ans,(choose(r-l+1,i)*p[i])%mod);
			}
			add(ans,keep[l][r]);
		}
		cout<<ans<<'\n';
	}
}
/*
(n18(3))^2 solution
dp[3][3][18][18]
given x,y (x= no. of forward and y=no. of backward)
x+y=digit
how many way to create a number where{
	x<A
	x>A
	x=A
	and also for y
}
3 operation to add to back,add to top

TC=digit^2*(nq)
*/