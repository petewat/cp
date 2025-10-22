#include "roads.h"
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
#define double long double
/*
*****
check if function has a return value?
*****
*/
const int mxn=1e5,inf=1e18,minf=-1e18,Mxn=1e7,lg=20;
int dp[mxn+10][2];
vector<pii>adj[mxn+10];
int k;
int del[mxn+10],vis[mxn+10],cost[mxn+10],p[mxn+10],inval[mxn+10];
struct fen{
  vector<pii>fwk;
  vector<pii>neighbor;
  void init(int x){
    for(auto i:adj[x])neighbor.pb({-i.s,i.f});
    neighbor.pb({minf,minf});
    sort(all(neighbor));
    fwk.assign(neighbor.size(),{0,0});
  }
  void update(int pos){
    if(pos==0)assert(0);
    pii val={neighbor[pos].f,1};
    for(int i=pos;i<fwk.size();i+=(i&-i))fwk[i].f+=val.f,fwk[i].s+=val.s;
  }
  pii qry(int pos){
    pii sum={0,0};
    for(int i=pos;i>0;i-=(i&-i))sum.f+=fwk[i].f,sum.s+=fwk[i].s;
    return sum; 
  }
  void put(pii a){
    auto it=lb(all(neighbor),a);
    if(it==neighbor.end())assert(0);
    update(it-neighbor.begin());
  }
  pii get(int x,int mx){
    //get all val<x and the cnt<mx
    if(mx<0)return {0,0};
    int pos=0,cnt=0,sum=0;
    for(int i=log2(neighbor.size())+1;i>=0;i--){
      if((pos+(1LL<<i))<neighbor.size()&&neighbor[pos+(1LL<<i)].f<x&&cnt+fwk[(pos+(1LL<<i))].s<=mx){
        pos+=(1LL<<i);
        cnt+=fwk[pos].s;
        sum+=fwk[pos].f;
      }
    }
    return {sum,cnt};
  }
}t[mxn+10];
int pref[mxn+10];
void solve(int cur,int p){
  if(del[cur])return;
  vis[cur]=1;
  int sum=inval[cur];//initial value (for the del children)
  vector<int>v;
  for(auto i:adj[cur]){
    if(i.f==p)continue;
    solve(i.f,cur);
    sum+=dp[i.f][1]+i.s;
    if(dp[i.f][0]-dp[i.f][1]-i.s<0)v.pb(dp[i.f][0]-dp[i.f][1]-i.s);//del all
  }
  dp[cur][0]=dp[cur][1]=sum;
  sort(all(v));//free sum
  v.pb(inf);
  for(int i=0;i<v.size();i++){
    pref[i]=v[i];
    if(i)pref[i]+=pref[i-1];
  }
  int a=t[cur].get(inf,k-1).f,b=t[cur].get(inf,k).f;
  for(int i=0;i<v.size()-1;i++){
    if(i+1<=k-1)a=min(a,pref[i]+t[cur].get(v[i+1],k-1-i-1).f);
    if(i+1<=k)b=min(b,pref[i]+t[cur].get(v[i+1],k-i-1).f);//cout<<"L\n";
  }
  dp[cur][0]+=a;
  dp[cur][1]+=b;
  //what am i smoking tryna bs???
}
/*
we have to somehow get the sum of k min val
for the edge of node ->alive can be handle normally but edge from node ->del
need to be handle seperately
*/
bool cmp(pii a,pii b){
  if(adj[a.f].size()!=adj[b.f].size())return adj[a.f].size()>adj[b.f].size();
  return a.f>b.f;
}
vector<int> minimum_closure_costs(int32_t N,vector<int32_t>U,vector<int32_t>V,vector<int32_t>W) {
  vector<int>ans;
  for(int i=0;i<N-1;i++){
    adj[U[i]].pb({V[i],W[i]});
    adj[V[i]].pb({U[i],W[i]});
  }
  vector<pii>node;
  for(int i=0;i<N;i++)node.pb({adj[i].size(),i}),sort(all(adj[i]),cmp),t[i].init(i);
  sort(all(node));
  int cur=0;
  for(int i=0;i<N;i++){
    k=i;
    while(cur<node.size()&&node[cur].f<=i){
      int x=node[cur].s;
      for(auto j:adj[x]){
        if(adj[j.f].empty())assert(0);
        if(adj[j.f].back().f!=x)assert(0);
        adj[j.f].pop_back();
        inval[j.f]+=j.s;
        t[j.f].put({-j.s,x});
      }
      del[x]=1;
      cur++;
    }
    int sum=0;
    for(int j=cur;j<node.size();j++){
      if(!vis[node[j].s]){
        solve(node[j].s,-1);
        sum+=dp[node[j].s][1];
      }
      vis[node[j].s]=0;
    }
    ans.pb(sum);
  }
  return ans;
}
#undef int
/*
int32_t main(){
  fastio
  int n;cin>>n;
  vector<int>u(n-1),v(n-1),w(n-1);
  for(int i=0;i<n-1;i++)cin>>u[i]>>v[i]>>w[i];//u[i]--,v[i]--;
  vector<ll>ans=minimum_closure_costs(n,u,v,w);
  for(auto i:ans)cout<<i<<" ";
  cout<<'\n';
}*/
/*
n^2 solution = do dp
dp[0],dp[1]; 0= didnt take par road,1= take par road
we can have atmost k dp[0];
we can sort dp[1]+road-dp[0] cost of all children
then greedy take
 
the sum of cnt of node with deg>=x = sum of deg ('O')
so we can actually do dp on these node and skip the node with deg<=x as we dont actually need to do anything to them
we can actually delete the unnecessary node and deal with each component independently?
*/