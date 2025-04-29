#include<bits/stdc++.h>
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
#define sz(x) (int)((x).size())
#define int long long
using namespace std;
const int mod=1e9+7,mxn=2e5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,d,q,T;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
set<int>have;
int v[mxn+10],cnt[mxn+10],sz[mxn+10];
set<int>val[mxn+10];
void add(int x,int a){
	if(sz[x])val[sz[x]].erase(val[sz[x]].find(x));
	if(sz[x]&&--cnt[sz[x]]==0)have.erase(have.find(sz[x]));
	sz[x]+=a;
	if(sz[x]&&++cnt[sz[x]]==1)have.insert(sz[x]);
	if(sz[x])val[sz[x]].insert(x);
}
//8 1 4 2 5 4 4 3
bool cmp(pii a,pii b){
	return a.f<b.f;
}
int32_t main(){
	fastio
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>v[i],sz[v[i]]++;
	for(int i=1;i<=n;i++)if(sz[i]){
		cnt[sz[i]]++,have.insert(sz[i]);
		val[sz[i]].insert(i);
	}
	vector<pii>T;
	int bro=0;
	while(q--){
		int a,b;cin>>a>>b;
		add(v[a],-1);
		v[a]=b;
		add(v[a],1);
		int ans=0,mx=(*prev(have.end()));
		T.clear();
		for(auto i:have)T.pb({i,(*prev(val[i].end()))});
		for(int i=have.size()-2;i>=0;i--)T[i].s=max(T[i].s,T[i+1].s);
		for(auto i:have){
			auto it=lb(all(T),make_pair(mx-i,0),cmp);
			if(it!=T.end())ans=max(ans,(*it).s-(*val[i].begin()));
		}
		cout<<ans<<'\n';
	}
}