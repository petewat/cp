#include "jumps.h"
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
#define double long double
/*
*****
check if function has a return value?
*****
*/
const int mxn=2e5,inf=1e9,minf=-1e9,Mxn=1e7,lg=20;;
#include <vector>
int l[mxn+10],r[mxn+10],n,val[mxn+10],up[lg+1][mxn+10],up2[lg+1][mxn+10];
bool yes=1;
struct seg{
  pii v[2*mxn+10];
  void build(){for(int i=n-1;i>=0;i--)v[i]=max(v[i*2],v[i*2+1]);}
  pii qry(int l,int r){
    pii ans={minf,0};
    for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
      if(l&1)ans=max(ans,v[l++]);
      if(!(r&1))ans=max(ans,v[r--]);
    }
    return ans;
  }
}t;
void init(int N, std::vector<int> H){
  stack<int>st;
  n=N;
  for(int i=0;i<n;i++)val[i]=H[i],t.v[i+n]={val[i],i};
  for(int i=1;i<n;i++)yes&=(val[i]>val[i-1]);
  for(int i=0;i<n;i++){
    while(!st.empty()&&val[st.top()]<val[i])st.pop();
    if(!st.empty())l[i]=st.top();
    else l[i]=n;
    st.push(i);
  }
  while(!st.empty())st.pop();
  for(int i=n-1;i>=0;i--){
    while(!st.empty()&&val[st.top()]<val[i])st.pop();
    if(!st.empty())r[i]=st.top();
    else r[i]=n;
    st.push(i);
  }
  t.build();
  val[n]=inf;
  for(int i=0;i<n;i++){
    int a=l[i],b=r[i];
    if(val[a]>val[b])swap(a,b);
    up2[0][i]=a;
    up[0][i]=b;
  }
  for(int j=0;j<=lg;j++)up[j][n]=n,up2[j][n]=n;
  for(int j=1;j<=lg;j++)for(int i=0;i<n;i++){
    up[j][i]=up[j-1][up[j-1][i]];
    up2[j][i]=up2[j-1][up2[j-1][i]];
  }
  n=N;
}
int ans=inf;
int solve(int a,int b,int c){
  if(a!=b){
    int bl=l[c]+1,br=r[c]-1;
    if(l[c]==n)bl=0;
    if(r[c]==n)br=n-1;
    if(b<bl||a>br)return inf;
    bl=max(bl,a),br=min(br,b);
    a=t.qry(bl,br).s;
  }
  int ans=0;
  for(int i=lg;i>=0;i--)if(val[up[i][a]]<val[c])a=up[i][a],ans+=(1LL<<i);
  if(up[0][a]==c)return ans+1;
  for(int i=lg;i>=0;i--)if(val[up2[i][a]]<val[c])a=up2[i][a],ans+=(1LL<<i);
  if(up2[0][a]==c)return ans+1;
  return inf;
}
int minimum_jumps(int a,int b,int c,int d){
  //c==d -> l[c]+1,r[c]-1 is possible so get max from that range
  //c!=d can we just get max c??
  //case 3 | 4 7
  int ans=inf;
  if(yes)ans=min(ans,solve(a,b,c));
  else for(int i=c;i<=d;i++)ans=min(ans,solve(a,b,i));
  if(ans==inf)return -1;
  return ans;
}
/*
how to get 100??? TT
*/
/*
int32_t main(){
  int n,q;cin>>n>>q;
  vector<int>v(n);
  for(int i=0;i<n;i++)cin>>v[i];
  init(n,v);
  while(q--){
    int a,b,c,d;cin>>a>>b>>c>>d;
    cout<<minimum_jumps(a,b,c,d)<<'\n';
  }
}*/
/*
sub (nq)=dijkstra
other{
  is it always better to go the direction with more value???? so bin lift??
  keep 2 binlift?
  first for max 2nd for jumping mn
}
*/