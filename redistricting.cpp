#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<cassert>
#include<limits.h>
#include<cmath>
#include<set>
#include<numeric> //gcd(a,b)
#include<algorithm>
#include<bitset> 
#include<stack>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define pppiiii pair<pii,pii>
#define ppii pair<int,pii>
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
//#define int long long
const int mod=1e9+7,mxn=6e5+5,lg=30,inf=1e9,minf=-1e9,Mxn=100000,root=700;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}	
int n,k;
int pref[mxn+10],ans[mxn+10];
bool d[mxn+10];
struct seg{
	int v[4*mxn+10];
	void init(int n){for(int i=0;i<=5*n;i++)v[i]=inf;}
	priority_queue<pii,vector<pii>,greater<pii>>pq[2*mxn+10];
	void add(int pos,int val,int id){
		pos+=2*n;
		if(id!=-1)pq[pos].push({val,id});
		else if(pq[pos].empty())pq[pos].push({val,id});
		if(pq[pos].empty())v[pos]=inf;
		else{
			if(pq[pos].top().f==v[pos])return;
			v[pos]=pq[pos].top().f;
		}
		for(int i=pos;i>0;i>>=1)v[i>>1]=min(v[i],v[i^1]);
	}
	void del(int pos,int id){
		if(id<0)return;
		pos+=2*n;
		d[id]=1;
		while(!pq[pos].empty()&&d[pq[pos].top().s])pq[pos].pop();
		add(pos-2*n,inf,-1);
	}
	int qry(int l,int r){
		int ans=inf;
		for(l+=2*n,r+=2*n;l<=r;l>>=1,r>>=1){
			if(l&1)ans=min(ans,v[l++]);
			if(!(r&1))ans=min(ans,v[r--]);
		}
		return ans;
	}
}t;
int32_t main(){
	setIO("redistricting");
	cin>>n>>k;
	string a;cin>>a;
	n++;
	for(int i=1;i<n;i++)pref[i]=((a[i-1]=='H')?1:-1)+((i==0)?0:pref[i-1]);
	for(int i=0;i<n;i++)pref[i]+=n;
	t.init(n);
	t.add(n,0,0);
	for(int i=1;i<n;i++){
		t.del(pref[i-k-1],i-k-1);
		ans[i]=min(t.qry(0,pref[i]-1),t.qry(pref[i],2*n+1)+1);
		t.add(pref[i],ans[i],i);
	}
	cout<<ans[n-1];
}