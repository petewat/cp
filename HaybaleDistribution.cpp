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
int n,k,m,base=109;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);	
}
int mx=0,a,b,pref[mxn+10];
vector<int>v;
int get(int x){
    int pos=upper_bound(all(v),x)-v.begin()-1;
    int ans=x*(a*(pos+1)-b*(n-pos-1));
    if(pos>=0)ans-=a*(pref[pos]);
    ans+=b*(pref[n-1]-pref[pos]);
    return ans;
}
int solve(){
    int l=0,r=mx,ans=inf;
    while(l<=r){
        int mid=l+(r-l)/2;
        int x=get(mid);
        if(get(mid-1)>=x)l=mid+1,ans=min(ans,x);
        else r=mid-1;
    }
    return ans;
}
int32_t main(){
    fastio
    cin>>n;
    v.resize(n);
    for(int i=0;i<n;i++)cin>>v[i],mx=max(mx,v[i]);
    sort(all(v));
    for(int i=0;i<n;i++){
        pref[i]=v[i];
        if(i)pref[i]+=pref[i-1];
    }
    int q;cin>>q;
    while(q--){
        cin>>a>>b;
        cout<<solve()<<'\n';
    }
}