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
const int mod=1e9+7,mxn=2000+5,inf=1e9,minf=-1e9,lg=30;
//#undef int
int n,k,m,x,y,n2;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);	
}
int p[mxn+10],p2[mxn+10];
int here[mxn+10],go[mxn+10];
int pa[mxn+10],lvl[mxn+10],D[mxn+10],deg[mxn+10];
set<int>child[mxn+10];
vector<int>adj[mxn+10];
int find(int u){return (pa[u]==u)?u:pa[u]=find(pa[u]);}
void merg(int a,int b){
    a=find(a),b=find(b);
    if(a==b)return;
    if(a<b)swap(a,b);
    for(auto i:child[b])child[a].insert(i);
    pa[b]=a;
    go[a]=max(go[a],go[b]);
}
void getlvl(int cur){for(auto i:child[cur])lvl[i]=lvl[cur]+1,getlvl(i);}
void getD(int cur){
    for(auto i:adj[cur])getD(i),D[cur]=max(D[cur],D[i]+1);
}
void re(){
    for(int i=1;i<=n;i++){
        deg[i]=lvl[i]=go[i]=D[i]=pa[i]=0;;
        p2[i]=p[i]=0;
        child[i].clear();
        adj[i].clear();
    }
}
int g=0;
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)pa[i]=i,deg[i]=0,here[i]=0,lvl[i]=0;
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        child[b].insert(a);
        deg[a]++;
        p[a]=b;
    }
    cin>>n2;
    for(int i=1;i<n2;i++){
        int a,b;cin>>a>>b;
        adj[b].pb(a);
        go[b]=max(go[b],a);
        p2[a]=b;
    }
    vector<pii>have;
    int root=0;
    for(int i=1;i<=n;i++)if(!deg[i])root=i;
    getlvl(root);
    getD(root);
    here[root]=1;
    int c=0;
    for(int i=1;i<=n;i++){
        if(p2[i]){
            int cur=i,cur2=i;
            for(int j=0;j<lvl[i];j++){
                cur=find(p[cur]),cur2=p2[cur2];
                if(cur==cur2)break;
                here[cur]=here[cur2]=1;
                if(find(p[cur])){
                    child[find(p[cur])].erase(child[find(p[cur])].find(cur));
                }
                merg(cur,cur2);
            }
        }
    }
    for(int i=1;i<=n;i++)have.pb({lvl[i],i});
    sort(all(have));
    for(int i=0;i<have.size();i++)if(!p2[have[i].s]&&!here[have[i].s]){
        int P=find(p[have[i].s]),X=0;
        for(auto j:child[P])if(j>have[i].s&&D[X]<=D[j])X=j;
        child[P].erase(child[P].find(have[i].s));
        merg(have[i].s,X);
    }
    int g=0;
    for(auto i:have){
        if(find(i.s)!=i.s)c++;
        else{
            for(auto j:child[i.s]){
                g++;
                if(p2[j]!=i.s)assert(0);
            }
        }
    }
    if(g!=n2-1)assert(0);
    cout<<c<<'\n';
    for(auto i:have)if(find(i.s)!=i.s)cout<<i.s<<" "<<find(i.s)<<'\n';
    re();
}

int32_t main(){
    int t;cin>>t;
    while(t--){
        g++;
        cout<<g<<'\n';
        solve();
    }
}
/*
when merging x,y
only the children node of y changes parent
*/