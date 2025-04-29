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
#define double long double
using namespace std;
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int ans[mxn+10],mark[mxn+10],T=1,mark2[mxn+10];
pii e[mxn+10];
vector<int>adj[mxn+10];
void dfs(int cur,int T){
    if(ans[cur])return;
    ans[cur]=T;
    for(auto i:adj[cur])if(!ans[i])dfs(i,T);
}
int32_t main(){
    fastio
	cin>>n>>q;
    vector<pair<int,pii>>qry;
	for(int i=0;i<q;i++){
		char x;cin>>x;
		if(x=='D'){
			int a;cin>>a;
            mark[a]=1;
            qry.pb({0,{a,0}});
		}
		else if(x=='A'){
            cin>>e[T].f>>e[T].s;
            qry.pb({1,{e[T].f,e[T].s}});
            T++;
		}
		else{
			int a;cin>>a;
            mark2[a]=1;
            qry.pb({2,{a,0}});
		}
	}
    for(int i=1;i<=T;i++)if(!mark2[i]){
        adj[e[i].f].pb(e[i].s);
        adj[e[i].s].pb(e[i].f);
    }
    for(int i=1;i<=n;i++)if(!mark[i])dfs(i,q);
    for(int i=q-1;i>=0;i--){
        if(qry[i].f==0)dfs(qry[i].s.f,i);
        else if(qry[i].f==2){
            adj[e[qry[i].s.f].f].pb(e[qry[i].s.f].s);
            adj[e[qry[i].s.f].s].pb(e[qry[i].s.f].f);
            if(ans[e[qry[i].s.f].f]!=0||ans[e[qry[i].s.f].s]!=0){
                dfs(e[qry[i].s.f].f,i);
                dfs(e[qry[i].s.f].s,i);
            }
        }
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}
/*


*/