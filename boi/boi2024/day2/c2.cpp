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
using namespace std;
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
void add(int &x,int y){
    x=(x+y)%mod;
    if(x<0)x=(x+mod);
}
int val[mxn+10][2],dp[mxn+10],cnt[mxn+10],val2[mxn+10][2],p[mxn+10];
int dpr[1001][1001];
int sum=0,sz;
vector<int>comp;
void solve(){
    for(int i=0;i<sz;i++)dp[i]=0,cnt[i]=0;
    cnt[val[0][0]]=1,cnt[val[0][1]]=1;
    for(int i=1;i<n;i++){
        if(val[i][0]>val[i][1])swap(val[i][0],val[i][1]);
        //dp[j] = sum of all ppssilbe ways where the left most is the max
        for(int j=0;j<val[i][0];j++)sum=(sum+(dp[j]*(p[n-1-i])%mod))%mod;
        //choose option 1
        for(int j=0;j<val[i][1];j++)sum=(sum+(dp[j]*(p[n-1-i])%mod))%mod;
        //option 2
        for(int j=val[i][1]+1;j<sz;j++){
            //2 option
            dp[j]=(dp[j]*2LL)%mod;
            dp[j]=(dp[j]+(cnt[j]*(comp[j]-comp[val[i][1]])%mod)%mod)%mod;
            dp[j]=(dp[j]+(cnt[j]*(comp[j]-comp[val[i][0]])%mod)%mod)%mod;
            cnt[j]=(cnt[j]*2LL)%mod;
        }
        for(int j=val[i][0]+1;j<=val[i][1];j++){
            //1 option
            dp[j]=(dp[j]+(cnt[j]*(comp[j]-comp[val[i][0]])%mod)%mod)%mod;
        }
        //create new one
        for(int j=val[i][1];j>=0;j--)cnt[val[i][1]]=(cnt[val[i][1]]+cnt[j])%mod;
        for(int j=0;j<val[i][0];j++)cnt[val[i][0]]=(cnt[val[i][0]]+cnt[j])%mod;
        //create new one
        for(int j=0;j<=val[i][0];j++){
            dp[j]=0;
            if(j!=val[i][0])cnt[j]=0;
        }
    }
}
void solve2(){
    for(int i=0;i<sz;i++)dp[i]=0,cnt[i]=0;
    cnt[val[0][0]]=1,cnt[val[0][1]]=1;
    for(int i=1;i<n;i++){
        //cout<<dp[0]<<" "<<cnt[0]<<" "<<dp[1]<<" "<<cnt[1]<<'\n';
        if(val[i][0]>val[i][1])swap(val[i][0],val[i][1]);
        //dp[j] = sum of all ppssilbe ways where the left most is the max
        for(int j=0;j<val[i][0];j++)sum=(sum+(dp[j]*(p[n-1-i])%mod))%mod;
        //choose option 1
        for(int j=0;j<val[i][1];j++)sum=(sum+(dp[j]*(p[n-1-i])%mod))%mod;
        //option 2
        for(int j=val[i][1]+1;j<sz;j++){
            //2 option
            dp[j]=(dp[j]*2LL)%mod;
            dp[j]=(dp[j]+(cnt[j]*(comp[j]-comp[val[i][1]])%mod)%mod)%mod;
            dp[j]=(dp[j]+(cnt[j]*(comp[j]-comp[val[i][0]])%mod)%mod)%mod;
            cnt[j]=(cnt[j]*2LL)%mod;
            
        }
        for(int j=val[i][0]+1;j<=val[i][1];j++){
            //1 option
            dp[j]=(dp[j]+(cnt[j]*(comp[j]-comp[val[i][0]])%mod)%mod)%mod;
        }
        //create new one
        for(int j=val[i][1];j>=0;j--)cnt[val[i][1]]=(cnt[val[i][1]]+cnt[j])%mod;
        for(int j=0;j<val[i][0];j++)cnt[val[i][0]]=(cnt[val[i][0]]+cnt[j])%mod;
        //create new one
        for(int j=0;j<=val[i][0];j++){
            dp[j]=0;
            if(j!=val[i][0])cnt[j]=0;
        }
    }
}
int32_t main(){
    fastio
    cin>>n;
    for(int i=0;i<n;i++)cin>>val[i][0],comp.pb(val[i][0]);
    for(int i=0;i<n;i++)cin>>val[i][1],comp.pb(val[i][1]);
    p[0]=1;
    for(int i=1;i<=n;i++)p[i]=(p[i-1]*2LL)%mod;
    sort(all(comp));
    comp.erase(unique(all(comp)),comp.end());
    for(int i=0;i<n;i++)val[i][0]=lb(all(comp),val[i][0])-comp.begin();
    for(int i=0;i<n;i++)val[i][1]=lb(all(comp),val[i][1])-comp.begin();
    sz=comp.size();
    solve();
    for(int i=0;i<n;i++)for(int j=0;j<2;j++)val2[n-1-i][j]=val[i][j];
    for(int i=0;i<n;i++)for(int j=0;j<2;j++)val[i][j]=val2[i][j];
    solve2();
    cout<<sum;
}
/*
4
1 1 1 1
2 2 2 2

4 3 2 3 4
would see it as 3-3
but its 3-4
so it wont count


*/