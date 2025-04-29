#include "grader.h"
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
using namespace std;
const int mod=998244353,mxn=1e5+5,inf=1e9,minf=-1e9,lg=21;
vector<int>adj[mxn+10];
int h[mxn+10],up[mxn+10][lg+1],n;
pii possub[mxn+10],push[mxn+10];
void dfs(int cur,int p){
    possub[cur]={1,1};
    vector<pii>v;
    for(auto i:adj[cur]){
        if(i==p)continue;
        h[i]=h[cur]+1;
        up[i][0]=cur;
        dfs(i,cur);
    }
    int add=1;
    for(auto i:adj[cur])if(i!=p){
        push[i].f+=add;
        add+=possub[i].f;
    }
    possub[cur].f=add;
    reverse(all(adj[cur]));
    add=1;
    for(auto i:adj[cur])if(i!=p){
        push[i].s+=add;
        add+=possub[i].s;
    }
    possub[cur].s=add;
}
void cal(int cur,int p){
    for(auto i:adj[cur])if(i!=p){
        push[i].f+=push[cur].f;
        push[i].s+=push[cur].s;
        cal(i,cur);
    }
}
void addRoad(int a, int b){
    adj[a].pb(b);
    adj[b].pb(a);
}
int before=-1;
int lca(int x,int y){
    if(h[x]<h[y])swap(x,y);
    int k=h[x]-h[y];
    before=-1;
    for(int i=lg;i>=0;i--)if(k&(1<<i))x=up[x][i];
    if(x==y)return x;
    for(int i=lg;i>=0;i--)if(up[x][i]!=up[y][i])x=up[x][i],y=up[y][i];
    before=x;
    return up[x][0];
}
void buildFarms(){
    n=getN();
    if(n==3)assert(0);
    dfs(0,-1);
    push[0]={1,1};
    cal(0,-1);
    for(int i=1;i<=lg;i++)for(int j=1;j<n;j++)up[j][i]=up[up[j][i-1]][i-1];
    for(int i=0;i<n;i++)setFarmLocation(i,push[i].f,push[i].s);
}
void notifyFJ(int a, int b){
    if(h[a]<h[b])swap(a,b);
    int node=lca(a,b);
    if(before==-1)ans(a,b);
    else if(before!=-1){
        ans(a,before);
        ans(node,b);
    }
}

/*
int32_t main(){
    int n;cin>>n;
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        addRoad(a,b);
    }
    buildFarms();
    for(int i=0;i<n;i++)cout<<push[i].f<<" "<<push[i].s<<"P\n";
    notifyFJ(0,0);
    notifyFJ(0,2);
}*/

/*
5
0 1
0 4
1 2
1 3

3
0 1
1 2
*/