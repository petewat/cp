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
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int dist[20][20],sum[(1LL<<18)],dp[(1LL<<18)][19];
int R[20];
struct line{
	int m,c;
	int get(int x){return (x*m)+c;}
};
double intersect(line a,line b){return (b.c-a.c)*1.0/(a.m-b.m);}
struct CHT{
	deque<line>dq;
	//add slope in increasing order
	//qry in increasing order
	//max convex hull
	void add(line a){
		while(dq.size()>1&&intersect(a,dq.back())<=intersect(a,dq[dq.size()-2]))dq.pop_back();
		dq.push_back(a);
	}
	int qry(int x){
		while(dq.size()>1&&dq[0].get(x)<=dq[1].get(x))dq.pop_front();
		if(dq.empty())assert(0);
		return dq[0].get(x);
	}

}t[20];
int32_t main(){
    fastio
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>R[i];
	for(int i=0;i<n;i++)for(int j=0;j<n;j++){
		if(i==j)continue;
		dist[i][j]=inf;
	}
	for(int i=0;i<m;i++){
		int a,b,t;cin>>a>>b>>t;
		a--,b--;
		dist[a][b]=t;
	}
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++)for(int j=0;j<n;j++){
			if(dist[i][k]!=inf&&dist[k][j]!=inf)dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
		}
	}
	for(int i=0;i<(1LL<<n);i++){
		for(int j=0;j<n;j++){
			dp[i][j]=minf;
			if(i&(1LL<<j))sum[i]+=R[j];
		}
	}
	for(int i=0;i<n;i++)dp[(1LL<<i)][i]=0;
	for(int i=1;i<(1LL<<n);i++){
		for(int last=0;last<n;last++){
			if(dp[i][last]==minf)continue;
			for(int j=0;j<n;j++)if(!(i&(1LL<<j))){
				if(dist[last][j]==inf)continue;
				dp[i+(1LL<<j)][j]=max(dp[i+(1LL<<j)][j],dp[i][last]-(sum[i]*dist[last][j]));
			}
		}
	}
	int q;cin>>q;
	vector<pair<pii,int>>qry(q);
	for(int i=0;i<q;i++)cin>>qry[i].f.f>>qry[i].f.s,qry[i].s=i,qry[i].f.s--;
	sort(all(qry));
	for(int i=0;i<n;i++){
		vector<pii>put;
		for(int j=0;j<(1LL<<n);j++){
			if(dp[j][i]==minf)continue;
			put.pb({sum[j],dp[j][i]});
		}
		sort(all(put));
		for(auto j:put)t[i].add((line){j.f,j.s});
	}
	vector<int>ans(q);
	for(int i=0;i<q;i++)ans[qry[i].s]=t[qry[i].f.s].qry(qry[i].f.f);
	for(auto i:ans)cout<<i<<'\n';

}
/*
*/