//#include "grader.h"
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
int n;
int val[1001][1001],on[1001][1001],vis[1001][1001];
pii pa[1001][1001],con[1001][1001];
pii find(int x,int y){
    if(pa[x][y].f==x&&pa[x][y].s==y)return {x,y};
    return pa[x][y]=find(pa[x][y].f,pa[x][y].s);
}
set<int>row[1001],col[1001];
pii in(int x,int y){
    if(on[x][y])return {-1,-1};
    //find what comp this cell is in
    pii a;
    auto it=row[x].lower_bound(y);
    a=find(x,(*it));
    if(it==row[x].begin())return {-1,-1};
    it--;
    if(a!=find(x,(*it)))return {-1,-1};
    it=row[y].lower_bound(x);
    if(a!=find((*it),y))return {-1,-1};
    if(it==row[y].begin())it--;
    if(a!=find((*it),y))return {-1,-1};
    return a;
}
int u[8]={-1,1,0,0,-1,-1,1,1},r[8]={0,0,1,-1,-1,1,-1,1};
void merg(pii a,pii b){

}
int32_t main(){
    cin>>n;
    vector<pair<int,pii>>v;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>val[i][j],v.pb({val[i][j],{i,j}}),pa[i][j]={i,j};
    sort(all(v));
    for(auto i:v){
        on[i.s.f][i.s.s]=1;
        for(int j=0;j<4;j++){
            int nx=i.s.f+u[j],ny=i.s.s+r[j];
            if(nx>n||nx<1||ny>n||ny<1)continue;
        }
    }
}