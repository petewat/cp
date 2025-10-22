#include "hexagon.h"
#include <vector>
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
#define int long long
const ll inf=1e9,minf=-1e9,mod=1e9+7;
map<pii,bool>mp;
pii go(int x){
  //diagonal =row
  if(x==1)return {-1,0};//go up by 1 row
  if(x==2)return {0,1};//go right 1 col
  if(x==3)return {1,1};//go down by 1 row and right 1 col
  if(x==4)return {1,0};//go down by 1 row
  if(x==5)return {0,-1};//go left by 1 col
  if(x==6)return {-1,-1};//go up by one and go left
}
int inv(ll x){
  int ex=mod-2;
  ll ans=1;
  x%=mod;
  while(ex){
    if(ex&1)ans=(ans*x)%mod;
    x=(x*x)%mod;
    ex>>=1;
  }
  return ans;
}
void add(pii &x,pii a){x={x.f+a.f,x.s+a.s};}
int32_t draw_territory(int32_t n, int32_t a, int32_t b,std::vector<int32_t> d, std::vector<int32_t> l) {
  ll x=0;
  for(auto i:l)x+=i;
  if(n==3){
    ll x=l[0];
    for(auto i:l)if(x!=i)assert(0);
    x++;
    ll sum=0,sum2=0;
    //i^2-i
    //meth
    sum=((x)*((x+1)%mod*(2*x+1)%mod)%mod)%mod;
    sum=(sum*inv(6LL))%mod;
    sum2=((x)*(x+1))%mod;
    sum2=(sum2*(inv(2LL)))%mod;
    sum=(sum-sum2+mod)%mod;
    sum=(sum*b)%mod;
    sum=(sum+sum2*a)%mod;
    return sum;
  }
  if(x>2000)return 0;
  pii cur={0,0};
  vector<pii>path;
  path.pb(cur);
  int mnx=inf,mny=inf;
  for(int i=0;i<n;i++){
    pii di=go(d[i]);
    for(int j=0;j<l[i];j++)add(cur,di),path.pb(cur);
  }
  for(auto i:path)mnx=min(mnx,i.f),mny=min(mny,i.s);
  if(mnx<0)mnx=-mnx;
  else mnx=0;
  if(mny<0)mny=-mny;
  else mny=0;
  for(auto &i:path)i.f+=mnx+1,i.s+=mny+1;
  int mxx=0,mxy=0;
  for(auto i:path)mxx=max(mxx,i.f),mxy=max(mxy,i.s);
  vector<vector<ll>>grid(mxx+2,vector<ll>(mxy+2,0)),dist(mxx+2,vector<ll>(mxy+2,inf));
  vector<vector<bool>>vis(mxx+2,vector<bool>(mxy+2,0));
  for(auto i:path)grid[i.f][i.s]=1;
  queue<pii>q;
  q.push({0,0});
  while(!q.empty()){
    pii cc=q.front();
    q.pop();
    for(int i=1;i<=6;i++){
      pii nx=cc;
      add(nx,go(i));
      if(nx.f<0||nx.s<0||nx.f>mxx+1||nx.s>mxy+1)continue;
      if(grid[nx.f][nx.s]||vis[nx.f][nx.s])continue;
      vis[nx.f][nx.s]=1;
      q.push({nx.f,nx.s});
    }
  }
  q.push({mnx+1,mny+1});
  dist[mnx+1][mny+1]=0;
  ll ans=0,aa=a,bb=b;
  while(!q.empty()){
    pii cc=q.front();
    q.pop();
    if(vis[cc.f][cc.s])continue;
    vis[cc.f][cc.s]=1;
    ll g=(bb*dist[cc.f][cc.s])%mod;
    if(dist[cc.f][cc.s]>inf)assert(0);
    g=(a+g)%mod;
    if(g<0)assert(0);
    ans=(ans+g)%mod;
    for(int i=1;i<=6;i++){
      pii nx=cc;
      add(nx,go(i));
      if(nx.f<0||nx.s<0||nx.f>mxx+1||nx.s>mxy+1)continue;
      if(vis[nx.f][nx.s]||dist[nx.f][nx.s]<dist[cc.f][cc.s]+1)continue;
      dist[nx.f][nx.s]=dist[cc.f][cc.s]+1;
      q.push({nx.f,nx.s});
    }
  }
  if(ans<0)assert(0);
  return ans;
}
#undef int
/*
int32_t main(){
  int n,a,b;cin>>n>>a>>b;
  vector<int>d(n),l(n);
  for(int i=0;i<n;i++)cin>>d[i];
  for(int i=0;i<n;i++)cin>>l[i];
  cout<<draw_territory(n,a,b,d,l);
  return 0;
}
*/
/*
17 2 3
1 2 3 4 5 4 3 2 1 6 2 3 4 5 6 6 1
1 2 2 1 1 1 1 2 3 2 3 1 6 3 3 2 1
*/