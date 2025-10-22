#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<algorithm>
#include<limits.h>
#include<set>
#include<cmath>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define ppii pair<pii,pii>
#define piii pair<pii,int>
#define all(x) x.begin(),x.end()
#define pll pair<ll,ll>
#define pb push_back
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#define double long double
#define int long long
#define mod 1000000007
const int mxn=1e5+5,lg=25;
int root=300;
int pos[mxn+10],ans[mxn+10],pa[mxn+10],sz[mxn+10];
int n,m;
bitset<mxn+10>on,yes;
stack<int>st;
vector<ppii>e;
int find(int u){
    while(u!=pa[u])u=pa[u];
    return u;
}
void re(){for(int i=0;i<=mxn;i++)pa[i]=i,sz[i]=1;}
void merg(int u,int v){
    int a=find(u),b=find(v);
    if(a==b)return;
    if(sz[a]>sz[b]){
        st.push(b);
        pa[b]=a;
        sz[a]+=sz[b];
        return;
    }
    st.push(a);
    pa[a]=b;
    sz[b]+=sz[a];
}
void rollback(int x){
    while(st.size()>x){
        int k=st.top();
        sz[pa[k]]-=sz[k];
        pa[k]=k;
        st.pop();
    }
}
void solve(vector<ppii>q){
    //first type
    //second type
    vector<pii>fq;
    vector<ppii>sq;
    on.reset();
    re();
    int cnt=0;
    for(auto i:q){
        if(i.f.s==-1)fq.pb({i.s.f,i.s.s}),cnt++;//id change
        else sq.pb({{i.s.s,i.s.f},{cnt,i.f.s}});//cost start cnt qryid
    }
    sort(sq.rbegin(),sq.rend());//by cost
    for(auto i:fq)on[i.f]=true;
    sort(e.rbegin(),e.rend());
    for(int i=0;i<e.size();i++)pos[e[i].f.s]=i;
    int cur=0;
    for(auto i:sq){
        while(cur<e.size()&&e[cur].f.f>=i.f.f){
            if(!on[e[cur].f.s])merg(e[cur].s.f,e[cur].s.s);
            cur++;
        }
        int x=st.size();
        yes.reset();
        for(int j=i.s.f-1;j>=0;j--){
            if(fq[j].s>=i.f.f&&(!yes[fq[j].f]))merg(e[pos[fq[j].f]].s.f,e[pos[fq[j].f]].s.s);
            yes[fq[j].f]=true;
        }
        for(int j=i.s.f;j<fq.size();j++)if(!yes[fq[j].f]&&e[pos[fq[j].f]].f.f>=i.f.f)merg(e[pos[fq[j].f]].s.f,e[pos[fq[j].f]].s.s);
        ans[i.s.s]=sz[find(i.f.s)];
        rollback(x);
    }
    for(auto i:fq)e[pos[i.f]].f.f=i.s;
}
int32_t main(){
    fastio
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,w;cin>>u>>v>>w;
        u--;
        v--;
        e.pb({{w,i},{u,v}});
    }
    int qr;cin>>qr;
    vector<ppii>q(qr);
    root=sqrt(qr);
    int cnt=0;
    for(int i=0;i<qr;i++){
        //1 id change
        //2 start weight
        cin>>q[i].f.f>>q[i].s.f>>q[i].s.s;
        q[i].f.s=((q[i].f.f==1)?-1:cnt++);
        q[i].s.f--;
    }
    int cur;
    for(int i=0;i<qr;i+=root){
        vector<ppii>cq;
        cur=i;
        while(cur<qr&&cur<i+root)cq.pb(q[cur++]);
        solve(cq);
    }
    for(int i=0;i<cnt;i++)cout<<ans[i]<<'\n';
    return 0;
}
