#include "coprobber.h"
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
const int mod=1e9+7,mxn=2e5+5,inf=1e9,minf=-1e9,lg=30,valbound=1e9;

using namespace std;

#define MAX_N 500
int vis[505],cur=0,n,dist[505][505];
int can[505][505],robber[505][505],m=0;
// modify the following functions
// you can define global variables and functions
void bfs(int root){
    queue<int>q;
    q.push(root);
    for(int i=0;i<n;i++)vis[i]=0;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        if(vis[cur])continue;
        vis[cur]=1;
        for(int i=0;i<n;i++)if(!vis[i]&&can[cur][i]){
            dist[root][i]=dist[root][cur]+1;
            q.push(i);
        }
    }
}
pii getcor(int x){return {x/m,x%m};}
int start(int N, bool A[MAX_N][MAX_N]){
    n=N;
    for(int i=0;i<n;i++){
        int cnt=0;
        for(int j=0;j<n;j++)can[i][j]=A[i][j],cnt+=can[i][j];
        if(cnt==2&&m==0)m=i;
    }
    m++;
    return 0;
}
int nextMove(int R){
    int go=-1;
    for(int i=0;i<n;i++)if(can[cur][R])return R;
    pii rob=getcor(R),pol=getcor(cur);
    rob.f-=pol.f,rob.s-=pol.s;
    if(rob.f==rob.s)return cur;
    if(rob.f<=1&&rob.s<=1)return cur;
    if(rob.f<rob.s)return cur=cur+1;
    return cur=cur+m;
}
// don't modify the main function
/*
if there exist a cycle size >4 then no solution exist
*/