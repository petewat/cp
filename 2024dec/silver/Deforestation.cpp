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
#define int long long
using namespace std;
const int mod=1e9+7,mxn=5e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int C[mxn+10],pref[mxn+10];
vector<pii> event[mxn+10];
void solve(){
    cin>>n>>k;
    vector<int>v(n);
    vector<int>comp;
    for(auto &i:v)cin>>i,comp.pb(i);;
    sort(all(v));
    vector<pair<pii,int>>re(k);
    for(auto &i:re){
        cin>>i.f.f>>i.f.s>>i.s;
        comp.pb(i.f.f);
        comp.pb(i.f.s);
    }
    sort(all(comp));
    comp.erase(unique(all(comp)),comp.end());
    for(auto &i:v){
        i=lb(all(comp),i)-comp.begin();
        C[i]++;
    }
    for(int i=0;i<comp.size();i++){
        pref[i]=C[i];
        if(i)pref[i]+=pref[i-1];
    }
    for(auto &i:re){
        i.f.f=lb(all(comp),i.f.f)-comp.begin();
        i.f.s=lb(all(comp),i.f.s)-comp.begin();
        i.s*=-1;
        i.s+=pref[i.f.s];
        if(i.f.f)i.s-=pref[i.f.f-1];
        event[i.f.f].pb({i.s,i.f.s});
    }
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    int ans=0;
    for(int i=0;i<comp.size();i++){
        while(!pq.empty()&&pq.top().s<i)pq.pop();
        for(auto j:event[i])pq.push({j.f+ans,j.s});
        for(int k=0;k<C[i];k++)if(pq.empty()||pq.top().f-ans>0){
            ans++;
        }
    }
    cout<<ans<<'\n';
    for(int i=0;i<comp.size();i++){
        C[i]=pref[i]=0;
        event[i].clear();
    }
}
int32_t main(){
    fastio
    int t;cin>>t;
    while(t--)solve();
}
/*
*/