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
const int mod=998244353,mxn=2e5+5,inf=1e9,minf=-1e9,lg=25;
int n,m,k,x,y;
int type[mxn+10],vis[mxn+10],dist[mxn+10],val[mxn+10];
int coeff[mxn+10];//
double ans[mxn+10];
vector<pii>adj[mxn+10];
stack<pii>st;
int found=0,huh[2]={1,-1};
bool haveans=1;
//chem exam gonna kill me tmr TT
void solve(int cur){
    vector<int>have;
    found=cur;
    while(!st.empty()&&st.top().f!=cur)have.pb(st.top().s),st.pop();
    have.pb(st.top().s),st.pop();
    if(have.size()%2==0)assert(0);
    reverse(all(have));
    ans[cur]=0;
    for(int i=0;i<have.size();i++)ans[cur]+=(huh[i%2]*type[have[i]]);
    ans[cur]=(ans[cur]*1.0/2);
}
void dfs(int cur,int p){
    vis[cur]=1;
    for(auto i:adj[cur]){
        if(i.f==p)continue;
        st.push({cur,i.s});
        if(vis[i.f]){
            //found a cycle, odd cycle -> even dist
            if((found==0)&&((dist[i.f]-dist[cur])%2==0))solve(i.f);
        }
        else dist[i.f]=dist[cur]+1,dfs(i.f,cur);
        if(!st.empty())st.pop();//push and backtrack
    }
}
void getans(int cur){
    for(auto i:adj[cur]){
        if(ans[i.f]!=inf){
            if((ans[cur]+ans[i.f])!=type[i.s])haveans=0;
        }
        else ans[i.f]=(type[i.s]-ans[cur]),getans(i.f);
    }
}
vector<int>comp;
void dfs2(int cur,int p){//all even cycle so we can do bipartite?
    vis[cur]=1;
    comp.pb(cur);
    for(auto i:adj[cur]){
        if(vis[i.f]&&(coeff[i.f]!=(!coeff[cur]))&&(val[i.f]!=type[i.s]-val[cur])){
            cout<<val[cur]<<" "<<val[i.f]<<" "<<type[i.s]<<'\n';
            haveans=0;//shouldnt exist
        }
        if(!vis[i.f]){
            coeff[i.f]=(!coeff[cur]);
            val[i.f]=type[i.s]-val[cur];
            dfs2(i.f,cur);
        }
    }
}
int32_t main(){
    fastio
    cin>>n>>m;
    for(int i=1;i<=n;i++)ans[i]=inf;
    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b>>type[i];
        adj[a].pb({b,i});
        adj[b].pb({a,i});
    }
    for(int i=1;i<=n;i++)if(!vis[i]){
        found=0;
        dfs(1,-1);
        while(!st.empty())st.pop();
        if(found)getans(found);
    }
    for(int i=1;i<=n;i++)vis[i]=0,val[i]=0,coeff[i]=1;
    vector<int>med;
    for(int i=1;i<=n;i++)if((!vis[i])&&ans[i]==inf){
        comp.clear();
        coeff[i]=1;
        val[i]=0;
        dfs2(i,-1);
        med.clear();
        for(auto j:comp)med.pb(huh[coeff[j]]*val[j]);
        sort(all(med));
        if((comp.size())%2)ans[i]=med[(n/2)];
        else ans[i]=(med[n/2]+med[(n/2)-1])*1.0/2;
        getans(i);
    }
    //0,-1
    if(!haveans)cout<<"NO\n";
    else{
        cout<<"YES\n";
        for(int i=1;i<=n;i++)if(ans[i]==inf)ans[i]=0;
        for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    }
    return 0;
    //step 1 find odd cycle
}
/*
observations:
-if there exist an odd cycle the value of the node in the cycle is fixed
because we will have equation like a+b=x,b+c=y.... then we can keep +,- the equation and solve for a
-if we know a value for atleast 1 node we can fill the whole graph

so first we can find if there exist an odd cycle 
-if it exist we can easily solve it
how to find an odd cycle?
dfs keep dist and stack
else?
we will be left with a graph that only have even cycle how to get min sum of abs(x)?
if we can find the value from x then we find other value by
edge cost-val coming from

so x<->a =1
val a=1-x
and b can be like 1-1+x=(x)
or like 2-1+x=(1+x)
we can find each val of node in form of y-x; where x is the starting node
now we want the sum of abs(y-x) for all y value to be min
if(x is negative then we can switch abs(y-x)=abs(x-y))
so 1-x new form will be x-1 and 1+x new form will still be x+1
now with equation like
abs(x-y1),abs(x-y2),abs(x-y3)....
now min sum will just be the min dist from x to all y so finding x is just finding median? of y val
*/