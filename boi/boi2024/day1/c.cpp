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
//#define ll long long
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
const int mod=1e9+7,mxn=1e5+5,inf=1e18,minf=-1e18,lg=62;
const int root=300;
int add[root+1][root+1];
int d[mxn+10],t[mxn+10];
vector<pair<pii,int>>del[mxn+10];
int dp[mxn+10];
int32_t main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++)cin>>d[i]>>t[i];
    int ans=0;
    dp[1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=root;j++)dp[i]=(dp[i]+add[j][i%j])%mod;
        if(d[i]<=root&&d[i]){
            add[d[i]][i%d[i]]=(add[d[i]][i%d[i]]+dp[i])%mod;
            if(i+(t[i]*d[i])<=n)del[i+(t[i]*d[i])].pb({{d[i],i%d[i]},dp[i]});
        }
        else if(d[i]){
            for(int j=1;(i+(j*d[i])<=n)&&j<=t[i];j++)dp[i+(j*d[i])]=(dp[i+(j*d[i])]+dp[i])%mod;
        }
        for(auto j:del[i]){
            add[j.f.f][j.f.s]=(add[j.f.f][j.f.s]-j.s)%mod;
            if(add[j.f.f][j.f.s]<0)add[j.f.f][j.f.s]=(add[j.f.f][j.f.s]+mod)%mod;
        }
        ans=(ans+dp[i])%mod;
    }
    cout<<ans;
}
/*
5
1 2
1 4
1 1
1 0
1 2

5
1 3
2 1
1 3
0 10
3 5
*/