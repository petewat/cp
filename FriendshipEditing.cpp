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
//#define int long long
#define double long double
using namespace std;
using cd = complex<double>;
double const PI=acos(-1);
const int mod=1e9+7,mxn=5e5+5,inf=1e9,minf=-1e9,lg=15,base=311;
//#undef int
int k,m,n,q,d;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
int yes[20][20];
int dp[(1LL<<20)];
int cost[1LL<<20];
int32_t main(){
	fastio
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b;cin>>a>>b;
		a--,b--;
		yes[a][b]=1;
		yes[b][a]=1;
	}
	int ans=m;
	for(int i=0;i<(1LL<<n);i++){
        for(int j=0;j<n;j++)if(i&(1LL<<j)){
            for(int k=j+1;k<n;k++)if(i&(1LL<<k)){
                if(yes[j][k])cost[i]++;
                else cost[i]--;
            }
        }
	}
    dp[0]=(n*(n-1))/2-m;
	for(int mask=1;mask<(1LL<<n);mask++){
		dp[mask]=inf;
		for(int i=mask;i>=0;i=(i-1)&mask){
            dp[mask]=min(dp[mask],dp[i]+cost[mask^i]);
            if(i==0)break;
		}
	}
	cout<<dp[(1LL<<n)-1];
}
/*

*/