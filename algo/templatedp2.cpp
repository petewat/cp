#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f first
#define s second
#define pii pair<int,int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#define sz(x) (int)((x).size())
const int mod=1e9+7,mxn=1e6,inf=1e9,minf=-1e9,lg=30,Mxn=1e9;
int n,m,q;
enum Type {Vertex,AddEdge,AddVertex,Compress,Rake};
vector<int>adj[mxn+10];
int root;
struct sttree{
	vector<int>P,L,R;
	int stroot,ct;
	vector<Type>T;
	sttree(){
		P.resize(4*n+1,-1),L.resize(4*n+1,-1),R.resize(4*n+1,-1);
		T.resize(4*n+1);
		ct=n;
		build();
	};
	private:
	int gethvy(int cur,int p){
		int best=0,sz=1;
		vector<int>na;
		for(auto i:adj[cur])if(i!=p)na.pb(i);
		swap(adj[cur],na);
		for(auto &i:adj[cur]){
			int x=gethvy(i,cur);
			if(x>best)best=x,swap(i,adj[cur][0]);
			sz+=x;
		}
		return sz;
	}
	int add(int cur,int l,int r,Type t){
		if(cur==-1)cur=++ct;
		T[cur]=t,L[cur]=l,R[cur]=r;
		if(l!=-1)P[l]=cur;
		if(r!=-1)P[r]=cur;
		return cur;
	}
	pii merge(vector<pii>have,Type t){
		if(have.empty())assert(0);
		if(have.size()==1)return have[0];
		vector<pii>l,r;
		int cs=0;
		for(auto i:have)cs+=i.s;
		for(auto i:have){
			if(cs>i.s)l.pb(i);
			else r.pb(i);
			cs-=2*i.s;
		}
		pii x=merge(l,t),y=merge(r,t);
		return {add(-1,x.f,y.f,t),x.s+y.s};
	}
	pii compress(int cur){
		vector<pii>have={addvertex(cur)};
		while(adj[cur].size())have.pb(addvertex(cur=adj[cur][0]));
		return merge(have,Type::Compress);
	}
	pii rake(int cur){
		vector<pii>have;
		for(int i=1;i<adj[cur].size();i++)have.pb(addedge(adj[cur][i]));
		return (have.empty())? (pii){-1,0} : merge(have,Type::Rake);
	}
	pii addvertex(int cur){
		pii x=rake(cur);
		return {add(cur,x.f,-1,(x.f==-1)? Type::Vertex: Type::AddVertex),x.s+1};
	}
	pii addedge(int cur){
		pii x=compress(cur);
		return {add(-1,x.f,-1,Type::AddEdge),x.s};
	}
	void build(){
		gethvy(root,-1);
		stroot=compress(root).f;
	}
};
struct point{
	int dp[2];
	point(){
		for(int i=0;i<2;i++)dp[i]=0;
	}
};
struct path{
	int dp[2][2];
	path(){
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)dp[i][j]=0;
	}
};
int val[mxn+10];
path compress(path a,path b){
	path x;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++){
		for(int k=0;k<2;k++)x.dp[i][j]=std::max(x.dp[i][j],a.dp[i][k]+b.dp[k^1][j]);
		x.dp[i][j]=std::max(x.dp[i][j],a.dp[i][0]+b.dp[0][j]);
	}
	return x;
}
point rake(point a,point b){
	for(int i=0;i<2;i++)a.dp[i]+=b.dp[i];
	return a;
}
point addedge(path a){
	point x;
	x.dp[0]=std::max(a.dp[0][1],a.dp[0][0]);
	x.dp[1]=std::max(a.dp[1][0],a.dp[1][1]);
	x.dp[1]=std::max(x.dp[0],x.dp[1]);
	return x;
}
path addvertex(point a,int cur){
	path x;
	x.dp[0][0]=a.dp[1];
	x.dp[1][1]=a.dp[0]+std::max(0,val[cur]);
	return x;
}
path vertex(int cur){
	path x;
	x.dp[1][1]=std::max(0,val[cur]);
	return x;
}
std::mt19937 rng(time(NULL));
int32_t main(){
	fastio
	std::cin>>n>>m;
	for(int i=1;i<=n;i++)std::cin>>val[i];
	for(int i=1;i<n;i++){
		int a,b;std::cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
    root=(rng()*rng())%n+1;
	sttree stt;
	vector<path>Path(4*n+1);
	vector<point>Point(4*n+1);
	auto update=[&](int x){
		if(stt.T[x]==Type::Vertex){
			Path[x]=vertex(x);
		}
		else if(stt.T[x]==Type::Rake){
			Point[x]=rake(Point[stt.L[x]],Point[stt.R[x]]);
		}
		else if(stt.T[x]==Type::Compress){
			Path[x]=compress(Path[stt.L[x]],Path[stt.R[x]]);
		}
		else if(stt.T[x]==Type::AddEdge){
			Point[x]=addedge(Path[stt.L[x]]);
		}
		else Path[x]=addvertex(Point[stt.L[x]],x);
	};
	function<void(int)>dfs=[&](int cur){
		if(stt.L[cur]!=-1)dfs(stt.L[cur]);
		if(stt.R[cur]!=-1)dfs(stt.R[cur]);
		update(cur);
	};
	dfs(stt.stroot);
	int last=0;
	while(m--){
		int x,y;std::cin>>x>>y;
		x^=last;
		val[x]=y;
		while(x!=-1)update(x),x=stt.P[x];
		last=addedge(Path[stt.stroot]).dp[1];
		std::cout<<last<<'\n';
	}
}
/*
*/