#include "paint.h"
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
#include <cstdlib> 
#include <cstdint>
using namespace std;
#define ll long long
#define f first
//#define endl "\n"
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
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
//#define int long long
/*
*/
const int mxn=2e5,mod=1e9+7,inf=1e9;
vector<pii>go[mxn+10];//for each col
int ans[mxn+10],mn[mxn+10];//ans=endpoint of using i
int dp[mxn+10];
int32_t minimumInstructions(int32_t n, int32_t m, int32_t k,vector<int32_t>c,vector<int32_t> A,vector<vector<int32_t>>B){
  for(int i=0;i<m;i++)for(auto j:B[i])go[j].pb({i,0});
  int cur=0;
  deque<pii>dq;
  dq.pb({-1,0});
  auto get=[&](int x){//will this work?
    while(dq.size()>=2&&dq[dq.size()-2].f>=x)dq.pop_back();
    if(dq.back().f>=x)return dq.back().s;
    return inf;
  };
  for(int i=0;i<=k;i++)mn[i]=inf;
  ans[0]=-1;
  for(int i=0;i<n;i++){
    for(auto &j:go[c[i]]){
      if(mn[j.f]!=inf)j.s=mn[j.f];
      else j.s=i;//start here
      if(i-j.s+1>=m){
        int x=get(i-m);
        if(x==inf)continue;
        ans[x+1]=i;
        dq.pb({i,x+1});
        cur=x+1;
      }
    }
    if(i)for(auto j:go[c[i-1]])mn[(j.f+1)%m]=inf;//clear
    for(auto j:go[c[i]])mn[(j.f+1)%m]=min(mn[(j.f+1)%m],j.s);//nxt start
  }
  if(ans[cur]<n-1)return -1;
  return cur;
}
/*
int32_t main(){
  int n,m,k;cin>>n>>m>>k;
  vector<int>c(n),a(m);
  vector<vector<int>>b(m);
  for(int i=0;i<n;i++)cin>>c[i];
  for(int i=0;i<m;i++){
    cin>>a[i];
    for(int j=0;j<a[i];j++){
      int x;cin>>x;
      b[i].pb(x);
    }
  }
  cout<<minimumInstructions(n,m,k,c,a,b);
}*/