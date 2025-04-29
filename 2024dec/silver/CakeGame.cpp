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
const int mod=1e9+7,mxn=5e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int v[mxn+10],pref[mxn+10];
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>v[i],pref[i]=v[i]+pref[i-1];
    int x=n-(n/2)+1;
    int ans=inf;
    for(int i=x;i<=n;i++)ans=min(ans,pref[i]-pref[i-x]);
    cout<<ans<<" "<<pref[n]-ans<<'\n';
}
int32_t main(){
    fastio
    int t;cin>>t;
    while(t--)solve();
}
/*
*/