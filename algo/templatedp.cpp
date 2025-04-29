#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define pii std::pair<int,int>
#define ppii std::pair<int,pii>
#define vi std::vector<int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio std::ios::sync_with_stdio(false);std::cin.tie(NULL);
//#pragma GCC optimize ("03,unroll-lopps")
#define sz(x) (int)((x).size())
//#define int long long
const int mod=1e9+7,mxn=1e6+5,inf=1e9,minf=-1e9,lg=30;
//#undef int
int n,k,m,d,q;
void setIO(std::string name){
	std::ios_base::sync_with_stdio(0); std::cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

struct mat{
	int M[2][2];
	mat(int a=0){
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)M[i][j]=0;
		M[1][0]=a;
	}
	void operator+=(mat &o){
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)M[i][j]+=o.M[i][j];
	}
	void operator-=(mat &o){
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)M[i][j]-=o.M[i][j];
	}
	mat operator*(mat o){
		if(o.M[0][0]==inf)return (*this);
		if(M[0][0]==inf)return o;
		mat c;
		c.M[0][0]=std::max(M[0][1]+o.M[1][0],M[0][0]+o.M[0][0]);
		c.M[1][0]=std::max(M[1][0]+o.M[0][0],M[1][1]+o.M[1][0]);
		c.M[0][1]=std::max(M[0][1]+o.M[1][1],M[0][0]+o.M[0][1]);
		c.M[1][1]=std::max(M[1][1]+o.M[1][1],M[1][0]+o.M[0][1]);
		return c;
	}
};
mat dummy;
mat mul;
void print(mat x){
	std::cout<<"PRINT\n";
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++)std::cout<<x.M[i][j]<<" ";
		std::cout<<'\n';
	}
}
int root;
struct seg{
	mat v[4*mxn+10];

	void update(int qpos,mat x,int pos=1,int l=1,int r=n){
		if(l>qpos||r<qpos)return;
		if(l==r)return void(v[pos]=x);
		update(qpos,x,pos<<1,l,((l+r)>>1));
		update(qpos,x,pos<<1|1,((l+r)>>1)+1,r);
		v[pos]=v[pos<<1]*v[pos<<1|1];
	}
	void updateA(int qpos,mat x,int pos=1,int l=1,int r=n){
		if(l>qpos||r<qpos)return;
		if(l==r)return void(v[pos]+=x);
		updateA(qpos,x,pos<<1,l,((l+r)>>1));
		updateA(qpos,x,pos<<1|1,((l+r)>>1)+1,r);
		v[pos]=v[pos<<1]*v[pos<<1|1];
	}
	mat qry(int ql,int qr,int pos=1,int l=1,int r=n){
		if(l>qr||r<ql)return dummy;
		if(ql<=l&&r<=qr)return v[pos];
		return qry(ql,qr,pos<<1,l,((l+r)>>1))*(qry(ql,qr,pos<<1|1,((l+r)>>1)+1,r));
	}
}t;

int val[mxn+10],hvy[mxn+10],hvyp[mxn+10],sz[mxn+10];
int tin[mxn+10],T=0,up[mxn+10],tail[mxn+10];
std::vector<int>adj[mxn+10];

void getsz(int cur,int p){
	sz[cur]=1;
	for(auto i:adj[cur])if(i!=p)getsz(i,cur),sz[cur]+=sz[i];
}
void hld(int cur,int p,int hp){
	tin[cur]=++T;
	tail[hp]=std::max(tail[hp],tin[cur]);
	hvyp[cur]=hp;
	for(auto i:adj[cur])if(i!=p&&sz[i]>sz[hvy[cur]])hvy[cur]=i;
	if(hvy[cur])hld(hvy[cur],cur,hp);
	for(auto i:adj[cur]){
		if(i==p)continue;
		up[i]=cur;
		if(i!=hvy[cur])hld(i,cur,i);
	}	
}

mat before[mxn+10];
int F[mxn+10][2];
void cal(int cur){
	cur=hvyp[cur];
	mat aft=(t.qry(tin[cur],tail[cur]));
	int x=aft.M[0][0],y=aft.M[1][0];
	mat delta;
	delta.M[0][0]=(std::max(x,y)-F[cur][0]);
	delta.M[0][1]=(std::max(x,y)-F[cur][0]);
	delta.M[1][0]=(x-F[cur][1]);
	F[cur][0]=std::max(x,y);
	F[cur][1]=x;
	if(up[cur]){
		t.updateA(tin[up[cur]],delta);
	}
}
void dfs(int cur,int p){
	mat U;
	U.M[1][0]=val[cur];
	U.M[1][1]=minf;
	t.update(tin[cur],U);
	for(auto i:adj[cur])if(i!=p)dfs(i,cur);
	if(cur==hvyp[cur])cal(cur);	
}
void update(int cur,int x){
	mat delta;
	delta.M[1][0]=x-val[cur];
	val[cur]=x;
	t.updateA(tin[cur],delta);
	while(hvyp[cur]!=root){
		cal(hvyp[cur]);
		cur=up[hvyp[cur]];
	}
}
std::mt19937 rng(time(NULL));
int32_t main(){
	fastio
	std::cin>>n>>m;
	for(int i=1;i<=n;i++)std::cin>>val[i];
	for(int i=0;i<n-1;i++){
		int a,b;std::cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dummy.M[0][0]=inf;
	root=(rng()*rng())%n+1;
	getsz(root,-1);
	hld(root,-1,root);
	dfs(root,-1);
	int last=0;
	while(m--){
		int x,y;std::cin>>x>>y;
		x^=last;
		update(x,y);
		mat ans=t.qry(tin[root],tail[root]);
		last=std::max(ans.M[0][0],ans.M[1][0]);
		std::cout<<last<<'\n';
	}
}
