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
const int mod=1e9+7,mxn=4e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
struct seg{
    int v[2*mxn+10];
    void init(){for(int i=0;i<=2*n;i++)v[i]=inf;}
    void update(int pos,int val){
        pos+=n;
        v[pos]=min(v[pos],val);
        for(int i=pos;i>0;i>>=1)v[i>>1]=min(v[i],v[i^1]);
    }
    int qry(int l,int r){
        int ans=inf;
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
            if(l&1)ans=min(ans,v[l++]);
            if(!(r&1))ans=min(ans,v[r--]);
        }
        return ans;
    }
}t;
int dp[mxn+10],go[mxn+10];
vector<int>st[mxn+10];
int32_t main(){
    fastio
    cin>>n>>m;
    vector<pii>v(n);
    vector<int>point;
    for(int i=0;i<n;i++){
        cin>>v[i].f>>v[i].s;
        if(v[i].s<v[i].f)v[i].s+=m;
        point.pb(v[i].f);
        point.pb(v[i].s);
    }
    sort(all(point));
    point.erase(unique(all(point)),point.end());
    for(int i=0;i<point.size();i++)go[i]=inf;
    for(auto &i:v){
        i.f=lb(all(point),i.f)-point.begin(),i.s=lb(all(point),i.s)-point.begin();
        go[i.s]=min(go[i.s],i.f);
        st[i.f].pb(i.s);
    }
    
    int ans=inf;
    if(n<=300){
        n=point.size();
        for(int i=0;i<point.size()-1;i++){
            if(st[i].empty())continue;
            int mn=inf;
            t.init();
            for(int j=0;j<point.size();j++)dp[j]=inf;
            dp[i]=0;
            t.update(i,0);
            for(int j=i+1;j<point.size();j++){
                if(go[j]!=inf){
                    dp[j]=min(dp[j],t.qry(go[j],j)+1);
                    t.update(j,dp[j]);
                }
                if(point[j]-m>=point[i])mn=min(mn,dp[j]);
            }
            ans=min(ans,mn);
        }
    }
    else{
        n=point.size();
        for(int i=0;i<point.size()-1;i++){
            int mn=inf;
            t.init();
            for(int j=0;j<point.size();j++)dp[j]=inf;
            dp[i]=0;
            t.update(i,0);
            for(int j=i+1;j<point.size();j++){
                if(go[j]!=inf){
                    dp[j]=min(dp[j],t.qry(go[j],j)+1);
                    t.update(j,dp[j]);
                }
            }
            int r=point.size()-1;
            for(int j=point.size()-1;j>=0;j--){
                while(r>=0&&point[r]-m>=point[j]){
                    mn=min(mn,dp[r]);
                    r--;
                }
                int curdp=inf;
                for(auto k:st[j])curdp=min(curdp,dp[k]);
                if(curdp==inf||mn==inf)continue;
                curdp--;
                ans=min(ans,mn-curdp);
            }
            break;
        }
    }
    if(ans>=inf)cout<<-1;
    else cout<<ans;
}
/*
8 100
10 30
30 50
50 70
40 60
60 80
50 70
80 100
100 20
 
4 100
0 30
30 70
70 100
60 20
 
1 100
30 40
*/