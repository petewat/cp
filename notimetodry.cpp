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
#include <iomanip>
#include<numeric>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
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
int n,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int col[mxn+10];
int root=440;
int tab[lg][mxn+10];
void buildtab(){
	for(int i=1;i<=lg;i++)for(int j=1;j+(1ll<<i)-1<=n;j++){
		tab[i][j]=min(tab[i-1][j],tab[i-1][j+(1ll<<(i-1))]);
	}
}
int get(int l,int r){
	int lvl=log2(r-l+1);
	return min(tab[lvl][l],tab[lvl][r-(1ll<<(lvl))+1]);
}
int ans[mxn+10];
int nxt[mxn+10],last[mxn+10],id[mxn+10];
int curans=0;
bool on[mxn+10];
bool cmp(pair<pii,int>a,pair<pii,int>b){return a.f.s<b.f.s;}
void solve(vector<pair<pii,int>>&v){
	int cr=1,cl=1,curans=1;
	for(int i=0;i<=n;i++)on[i]=0;
	for(auto i:v){
		while(cr<i.f.s){
			cr++;
			if(last[cr]>=i.f.f&&get(last[cr],cr)>=col[cr])on[cr]=1;
			else curans++;
		}
		while(cl>i.f.f){
			cl--;
			if(nxt[cl]!=0&&on[nxt[cl]]==0&&nxt[cl]<=i.f.s&&get(cl,nxt[cl])>=col[cl])on[nxt[cl]]=1;
			else curans++;
		}
		while(cl<i.f.f){
			if(on[nxt[cl]])on[nxt[cl]]=0;
			else curans--;
			cl++;
		}
		ans[i.s]=curans;
	}
	while(cl<=n)on[cl++]=0;
}
bool cmp2(pair<pii,int>a,pair<pii,int>b){
	if((a.f.f/root)!=(b.f.f/root))return (a.f.f/root)<(b.f.f/root);
	return a.f.s<b.f.s;
}
int32_t main(){
	fastio
	cin>>n>>q;
	root=500;
	for(int i=1;i<=n;i++)cin>>col[i];
	vector<pair<pii,int>>qry(q);
	for(int i=0;i<q;i++)cin>>qry[i].f.f>>qry[i].f.s,qry[i].s=i;
	sort(all(qry),cmp2);
	for(int i=1;i<=n;i++)tab[0][i]=col[i];
	for(int i=1;i<=n;i++)last[i]=id[col[i]],id[col[i]]=i;
	fill(id,id+n+1,0);
	for(int i=n;i>=1;i--)nxt[i]=id[col[i]],id[col[i]]=i;
	buildtab();
	int cur=0;
	for(int i=0;i<qry.size();i++){
		vector<pair<pii,int>>v;
		while(cur<qry.size()&&((qry[cur].f.f/root)==(qry[i].f.f/root))){
			v.pb(qry[cur]);
			cur++;
		}
		solve(v);
		i=cur-1;
	}
	for(int i=0;i<q;i++)cout<<ans[i]<<'\n';
}
/*
8 5
1 2 2 1 1 2 3 2
4 6
3 6
1 6
5 8
6 8

8 2
1 2 2 1 1 2 3 2
4 6
5 8

8 1
1 2 2 1 1 2 3 2
4 6

3 3
2 1 2
1 2
2 3
1 3

8 3
1 2 3 5 6 2 1 3
1 7
2 6
2 3
so given a range of number find min number of paint needed


need to paint the lower number first

so if 2 position with same color

X a a c b c X
we can connect this X with the other X if and only if
everything between X is more than X
so we want to count the number of pair a,b and range l,r
that min(a+1,b-1)>col[a];

we can use mos algorithm
sort range by l,r
when move r increasing we simply maintain the last occurence of that color and see if we can continue from that
if we cant ans++;
l need to be move both increasing and decreasing
when decrease/introduce new element we simply do the same but now we need to keep the first occurence
then when increase/delete
we want to know if the next occurence is connected if it is then nothing change
else ans--;


so on[i]= i is connected to last i

when move r and introduce new r when can check if the r is connected to the last i
iff lasti is >= i.f.f and get(lasti,i)<=col[i]


when mov l/delete l
we can check if the nxtl is on=same component as the cur then we dont need to do anything
else ans--;
when itroduced new l we can check the nxtl is valid
*/