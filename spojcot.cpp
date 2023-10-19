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
#define pii pair<ll,ll>
#define ppii pair<pii,pii>
#define vi vector<int>
#define pb push_back
//#define p push
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
const int mxn=1e5,lg=25;
struct node{
	node *l,*r;
	int val;
	node():val(0),l(0),r(0){}
};
node *root[mxn+10];
vector<int>adj[mxn+10],com;
int g[mxn+10],h[mxn+10],up[mxn+10][lg+5],cn,pos[mxn+10];
void build(node*&a,int l,int r){
	a=new node();
	if(l==r)return;
	int mid=l+(r-l)/2;
	build(a->l,l,mid);
	build(a->r,mid+1,r);
}
void update(node *&ncur,node *lcur,int l,int r,int pos){
	ncur=new node(*lcur);
	if(l==r){
		if(r==pos)ncur->val++;
		return;
	}
	int mid=l+(r-l)/2;
	if(pos<=mid)update(ncur->l,ncur->l,l,mid,pos);
	else update(ncur->r,ncur->r,mid+1,r,pos);
	ncur->val=ncur->l->val+ncur->r->val;
}
int qry(node *a,node *b,node *c,int l,int r,int q){
	if(l==r)return l;
	int mid=l+(r-l)/2;
	int lm=(a->l->val)+(b->l->val)-(2*c->l->val)+(l<=pos[cn]&&mid>=pos[cn]);
	if(lm>=q)return qry(a->l,b->l,c->l,l,mid,q);
	else return qry(a->r,b->r,c->r,mid+1,r,q-lm);
}
void dfs(int cur,int p){
    auto it=lb(all(com),g[cur]);
    pos[cur]=it-com.begin();
	update(root[cur],root[p],0,mxn+5,pos[cur]);
	for(auto i:adj[cur]){
		if(i==p)continue;
		h[i]=h[cur]+1;
		up[i][0]=cur;
		dfs(i,cur);
	}
}
int lca(int u,int v){
	if(h[v]<h[u])swap(u,v);
	int k=h[v]-h[u];
	for(int i=0;i<=lg;i++)if(k&(1<<i))v=up[v][i];
	if(u==v)return v;
	for(int i=lg;i>=0;i--){
		if(up[v][i]!=up[u][i]){
			v=up[v][i];
			u=up[u][i];
		}
	}
	return up[u][0];
}
int main(){
	int n,q;cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>g[i],com.pb(g[i]);
    sort(all(com));
	build(root[0],0,mxn+5);
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs(1,0);
	for(int j=1;j<=lg;j++)for(int i=1;i<=n;i++)up[i][j]=up[up[i][j-1]][j-1];
	while(q--){
		int u,v,k;cin>>u>>v>>k;
		cn=lca(u,v);
		cout<<com[qry(root[u],root[v],root[cn],0,mxn+5,k)]<<'\n';
	}
}
