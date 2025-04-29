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
#define ll long long
#define f first
#define endl "\n"
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
using namespace std;
#define int long long
#define double long double
const int mod=1e9+7,mxn=1e5+5,lg=30,inf=1e18,minf=-1e18;
int n,root=0;
vector<int>A[mxn+10];
int v[mxn+10],ans[mxn+10],ans2[mxn+10];
void solvesmall(int id){
    for(int i=1;i<=A[id].size();i++){
        //find min max sum for each comp
        int l=0,r=n,val=inf;
        while(l<=r){
            int mid=l+(r-l)/2,C=1,CS=A[id][0];
            for(auto j:A[id])if(j-CS>mid){
                C++;
                CS=j;
            }
            if(i>=C)val=min(val,mid),r=mid-1;
            else l=mid+1;
        }
        if(val==inf)assert(0);
        ans[val-1]++;
    }
}
void solvebig(int id){
    for(int i=1;i<=n;i++){
        int C=0,cnt=0;
        while(C<A[id].size()){
            C=upper_bound(all(A[id]),A[id][C]+i)-A[id].begin();
            cnt++;
        }
        if(cnt>(n/i)+1)assert(0);
        ans2[i]+=cnt;
    }
}
int32_t main(){
    fastio
    cin>>n;
    int K=0;
    root=sqrt(n*100);
    for(int i=1;i<=n;i++)cin>>v[i],A[v[i]].pb(i);
    for(int i=1;i<=n;i++){
        if(A[i].empty())continue;
        if(A[i].size()<=root){
            solvesmall(i);
            K++;
        }
        else solvebig(i);
    }
    for(int i=n;i>=1;i--)ans[i]+=ans[i+1];
    for(int i=1;i<=n;i++)cout<<K+ans[i]+ans2[i]<<'\n';
}