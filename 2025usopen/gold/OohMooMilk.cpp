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
const int mod=1e9+7,mxn=2e5,inf=1e18,minf=-1e18,lg=30,Mxn=1e6;
//#undef int
int n,k,m,d,q,T;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
int v[mxn+10],A,B;
struct fen{
	int fwk[mxn+10];
	void update(int pos,int val){
		if(pos<=0)return;
		for(int i=pos;i<=n;i+=(i&-i))fwk[i]+=val;
	}
	int qry(int pos){
		if(pos<=0)return 0;
		int sum=0;
		for(int i=pos;i>0;i-=(i&-i))sum+=fwk[i];
		return sum;
	}
	int find(int x){
		//find last <=x
		int pos=0,sum=0;
		for(int i=lg;i>=0;i--)if(pos+(1LL<<i)<=n&&sum+fwk[pos+(1LL<<i)]<=x){
			pos+=(1LL<<i);
			sum+=fwk[pos];
		}
		return pos;
	}
}t;
void update(int a,int b){
	t.update(a-b+1,1);
	t.update(a+1,-1);
}
void solve(){
	vector<int>v(n);
	for(auto &i:v)cin>>i;
	for(int i=0;i<d;i++){
		sort(rall(v));
		for(int i=0;i<n;i++){
			if(i<A&&i>=B)v[i]++;
		}
	}
	int ans=0;
	for(auto i:v)ans=(ans+(i*i)%mod)%mod;
	cout<<ans;
}
void solve2(){
	vector<int>v(n);
	for(auto &i:v)cin>>i;
	sort(all(v));
	for(int i=0;i<v.size();i++){
		if(i)t.update(i+1,v[i]-v[i-1]);
		else t.update(i+1,v[i]);
	}
	for(int i=0;i<d;i++){
		int x=t.qry(n-B);
		int L=t.find(x-1)+1,R=t.find(x);
		int use=n-B-L+1;
		update(R,use);
		update(L-1,A-B-use);
	}
	int ans=0;
	for(int i=1;i<=n;i++)ans=(ans+(t.qry(i)*t.qry(i))%mod)%mod;
	if(ans<0)assert(0);
	cout<<ans;
}
int32_t main(){
	fastio
	cin>>n>>d;
	cin>>A>>B;
	if(n<=1000&&d<=1000){
		solve();
		return 0;
	}
	if(d<=Mxn){
		solve2();
		return 0;
	}
	vector<int>v(n);
	int sum=0;
	for(auto &i:v)cin>>i,sum=(sum+i)%mod;
	cout<<sum;
}