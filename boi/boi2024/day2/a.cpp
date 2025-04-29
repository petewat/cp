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
const int mod=1e9+7,mxn=1e6+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int sz=0;
struct seg2{
    pii v[2*mxn+10];
    void init(){for(int i=0;i<=2*sz;i++)v[i]={minf,minf};}
    void update(int pos,pii val){
        pos+=sz;
        v[pos]=max(v[pos],val);
        for(int i=pos;i>0;i>>=1)v[i>>1]=max(v[i],v[i^1]);
    }
    pii qry(int l,int r){
        pii ans={minf,minf};
        for(l+=sz,r+=sz;l<=r;l>>=1,r>>=1){
            if(l&1)ans=max(ans,v[l++]);
            if(!(r&1))ans=max(ans,v[r--]);
        }
        return ans;
    }
}t2;
vector<int>adj[mxn+10];
int ans=inf;
vector<pii>v,v2;
vector<int>point;
int up[mxn+10][lg+1],up2[mxn+10],bruh[mxn+10];
int32_t main(){
    fastio
    cin>>n>>m;
    v.resize(n);
    for(int i=0;i<n;i++){
        cin>>v[i].f>>v[i].s;
        if(v[i].f>v[i].s){
            point.pb(v[i].f);
            point.pb(v[i].s+m+1);
        }
        else{
            point.pb(v[i].f);
            point.pb(v[i].s);
            point.pb(v[i].f+m+1);
            point.pb(v[i].s+m+1);
        }
    }
    sort(all(point));
    point.erase(unique(all(point)),point.end());
    int id=0;
    sz=point.size();
    t2.init();
    for(auto &i:v){
        v2.pb({i.f,i.s});
        if(i.f<i.s){
            t2.update(lb(all(point),i.f)-point.begin(),{lb(all(point),i.s)-point.begin(),id});
            t2.update(lb(all(point),i.f+m+1)-point.begin(),{lb(all(point),i.s+m+1)-point.begin(),id});
            i.f=lb(all(point),i.f)-point.begin(),i.s=lb(all(point),i.s)-point.begin();
        }
        else{
            t2.update(lb(all(point),i.f)-point.begin(),{lb(all(point),i.s+m+1)-point.begin(),id});
            i.f=lb(all(point),i.f)-point.begin(),i.s=lb(all(point),i.s+m+1)-point.begin();
        }
        id++;
    }
    for(int i=0;i<n;i++){
        if(v2[i].f<v2[i].s){
            int go=t2.qry(v[i].f,v[i].s).s;
            if(go!=minf&&go!=i)up[i][0]=go;
            else up[i][0]=i,bruh[i]=1;
        }
        else{
            int go=t2.qry(v[i].f,v[i].s).s;
            up[i][0]=i;
            if(go==i)bruh[i]=1;
            up2[i]=go;
        }
    }
    for(int i=1;i<=lg;i++)for(int j=0;j<n;j++)up[j][i]=up[up[j][i-1]][i-1];
    for(int i=0;i<n;i++){
        int x=up[i][lg],cnt=1,cur=i;
        if(bruh[cur])continue;
        for(int j=lg;j>=0;j--)if(up[cur][j]!=x)cur=up[cur][j],cnt+=(1LL<<j);
        if(cur!=x)cur=up[cur][0],cnt++;
        if(bruh[cur])continue;
        while(v2[cur].f>v2[cur].s){
            cur=up2[cur];
            cnt++;
            if(bruh[cur])break;
            if(v2[cur].s>=v2[i].f)break;
        }
        x=up[cur][lg];
        if(bruh[cur])continue;
        if(v2[cur].s>=v2[i].f){
            ans=min(ans,cnt);
            continue;
        }
        for(int j=lg;j>=0;j--)if(up[cur][j]!=x&&v2[up[cur][j]].s<v2[i].f)cur=up[cur][j],cnt+=(1LL<<j);
        if(bruh[cur])continue;
        cur=up[cur][0];
        if(bruh[cur])continue;
        cnt++;
        if(v2[cur].s>=v2[i].f||cur==x)ans=min(ans,cnt);
    }
    if(ans>=inf)cout<<-1;
    else cout<<ans;
}
/*
12
58
66
68
92
125
150
175
223
269
288
291
3

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