#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<limits.h>
#include<cmath>
#include<set>
#include<algorithm>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define ppii pair<int,pii>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
#define int long long
const int mxn=1e5,mod=1000000007,lg=20,root=1000,inf=1e18;
int dist[mxn+10],dp[mxn+10],ans[mxn+10],consize=0,cs[mxn+10];
pii info[mxn+10];
vector<pii>adj[mxn+10];
struct line{int m,c;};
line con[mxn+10];
double intersect(line a,line b){return ((b.c-a.c)*1.0/(a.m-b.m)*1.0);}
static bool cmp(pair<pii,line>a,pair<pii,line>b){return a.f<b.f;}
bitset<mxn+10>on;
int rem(line a){//finding next pos
    int l=1,r=consize-1;
    if(consize<2)return consize;
    if(intersect(a,con[consize-1])>=intersect(con[consize-1],con[consize-2]))return consize;
    while(l<r){
        int mid=l+(r-l)/2;
        if(intersect(a,con[mid])<intersect(con[mid],con[mid-1]))r=mid;
        else l=mid+1;
    }
    return l;
}
int qry(int x){//rate bs
    int l=0,r=consize-1;
    while(l<r){
        int mid=l+(r-l)/2;
        if(intersect(con[mid],con[mid+1])<x)l=mid+1;
        else r=mid;
    }
    return (x*con[l].m)+con[l].c;
}
/*dp i =dp[j]+(di-dj)*ratei+sti
dpj+di(ratei)-dj(ratei)+sti
m=ratei(dj)
c=dpj
y=-(x)*dcur+dpcur ->slope monotonic
x=ratei->not monotonic=bs
*/
int t=0;
void dfs(int cur,int p){
    if(cur!=1)dp[cur]=qry(info[cur].s)+info[cur].f+(info[cur].s*dist[cur]);
    line n={-dist[cur],dp[cur]};
    pair<pii,line> change;
    change.f.f=consize;
    change.f.s=consize=rem(n);//new pos to add
    change.s=con[consize];
    con[consize++]=n;
    for(auto i:adj[cur]){
        if(i.f==p)continue;
        dist[i.f]=dist[cur]+i.s;
        dfs(i.f,cur);
    }
    if(cur!=-1){
        con[change.f.s]=change.s;
        consize=change.f.f;
    }
}
int32_t main(){
    fastio
    int n;cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v,w;cin>>u>>v>>w;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
    for(int i=2;i<=n;i++)cin>>info[i].f>>info[i].s;//st rate
    dfs(1,-1);
    for(int i=2;i<=n;i++)cout<<dp[i]<<" ";
}
