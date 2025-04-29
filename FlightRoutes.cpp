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
int n,k,m,x,y,vx,vy;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);	
}
int have[800][800],par[800][800];
int32_t main(){
    fastio
    cin>>n;
    for(int i=1;i<=n;i++){
        string a;cin>>a;
        for(int j=0;j<a.size();j++)par[i][i+j+1]=a[j]-'0';
    }
    int ans=0;
    for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){
        int sum=0;
        for(int k=i+1;k<j;k++)if(have[i][k])sum+=par[k][j];
        if((sum%2)!=par[i][j])have[i][j]=1;
        ans+=have[i][j];
    }
    cout<<ans;
}
/*
*/