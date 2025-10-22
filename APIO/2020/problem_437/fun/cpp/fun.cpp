#include "fun.h"
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
#define sz(x) (int)((x).size())
const int mxn=1e5,minf=-1e7;
vector<int>adj[mxn+10];
int done[mxn+10],dist[1001][1001],n;
pii st;
void getdist(int cur,int p,int root){
  st=max(st,{dist[root][cur],root});
  for(auto i:adj[cur])if(i!=p){
    dist[root][i]=dist[root][cur]+1;
    getdist(i,cur,root);
  }
}
struct seg{
  pii v[2*mxn+10];
  void update(int pos,int val,int id){
    pos+=n;
    v[pos]={val,id};
    for(int i=pos;i>0;i>>=1)v[i>>1]=max(v[i],v[i^1]);
  }
  pii qry(int l,int r){
    pii ans={minf,0};
    for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
      if(l&1)ans=max(ans,v[l++]);
      if(!(r&1))ans=max(ans,v[r--]);
    }
    return ans;
  }
}t;
vector<int> createFunTour(int N, int Q){
  n=N;
  vector<int>ans;
  if(n<=500){
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(hoursRequired(i,j)==1){
      adj[i].pb(j);
      adj[j].pb(i);
    }
    st={-1,0};
    for(int i=0;i<n;i++)getdist(i,-1,i);
    while(ans.size()<n){
      int cur=st.s;
      ans.pb(cur);
      done[cur]=1;
      st={-1,0};
      for(int j=0;j<n;j++)if(!done[j])st=max(st,{dist[cur][j],j});
    }
  }
  else{
    for(int i=1;i<n;i++){
      adj[(i-1)/2].pb(i);
      adj[i].pb((i-1)/2);
    }
    vector<int>dept(n,0),tin(n,0),tout(n,0);
    int T=0;
    function<void(int,int)>dfs=[&](int cur,int p){
      tin[cur]=T++;
      for(auto i:adj[cur])if(i!=p)dfs(i,cur);
      tout[cur]=T-1;
    };
    dfs(0,-1);
    for(int i=0;i<n;i++){
      int x=i;
      while(x)dept[i]++,x=(x-1)/2;
      t.update(tin[i],dept[i],i);
    }
    st={minf,0};
    auto get=[&](int cur){
      int x=cur;
      pii y=t.qry(tin[x],tout[x]);
      st={minf,0};
      st=max(st,{y.f-dept[x],y.s});
      while(x){
        int g=1;
        if(x%2==0)g=-1;
        pii y=t.qry(tin[x+g],tout[x+g]);
        st=max(st,{y.f-2*(dept[x]-1),y.s});
        x=(x-1)/2;
        st=max(st,{-dept[x],x});
      }
      return st;
    };
    for(int i=0;i<n;i++)st=max(st,get(i));
    while(ans.size()<n){
      int cur=st.s;
      ans.pb(cur);
      t.update(tin[cur],minf,cur);
      st=get(cur);
    }
  }
  return ans;
}

/*
15 40000
0 1
0 2
1 3
1 4
3 7
3 8
4 9
4 10
2 5
2 6
5 11
5 12
6 13
6 14
*/