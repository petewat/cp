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
int n,k,m,a,b;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int dpp[2002][2002],dps[2002][2002];
int32_t main(){
    fastio
    cin>>n>>a>>b;
    vector<pair<int,pii>>v(n);
    //rate cost popularity
    for(auto &i:v)cin>>i.s.s>>i.s.f>>i.f;
    sort(all(v));
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<=b;j++)if(i)dpp[i][j]=dpp[i-1][j];
        for(int j=b;j>=0;j--){
            if(j>=v[i].f*v[i].s.f)dpp[i][j]=max(dpp[i][j],dpp[i][j-v[i].f*v[i].s.f]+v[i].s.s);
            ans=max(ans,dpp[i][j]);
        }
    }
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<=a;j++){
            dps[i][j]=dps[i+1][j];
            if(j>=v[i].s.f)dps[i][j]=max(dps[i][j],dps[i+1][j-v[i].s.f]+v[i].s.s);
            ans=max(ans,dps[i][j]);
        }
    }
    for(int i=0;i<n;i++)for(int j=0;j<=a;j++){
        int need=(v[i].s.f-a+j)*v[i].f;
        if(need>b)continue;
        if(i)ans=max(ans,v[i].s.s+dps[i+1][j]+dpp[i-1][min(b,b-need)]);
        else ans=max(ans,v[i].s.s+dps[i+1][j]);
    }
    cout<<ans;
}
/*

*/