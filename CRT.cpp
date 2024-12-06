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
pii euclid(int x,int y){
    if(y==0)return {1,0};
    pii a=euclid(y,x%y);
    swap(a.f,a.s);
    a.s-=(a.f*(x/y));
    return a;
}
pii merge(pii a,pii b){
    if(a.s<b.s)swap(a,b);
    pii coef=euclid(a.s,b.s);
    return {((a.f*coef.s*b.s)+(b.f*coef.f*a.s))%(a.s*b.s),a.s*b.s};
}
void solve(){
    cin>>n;
    vector<pii>v(n);
    for(int i=0;i<n;i++)cin>>v[i].s>>v[i].f;
    //{a,m}
    for(int i=1;i<n;i++)v[i]=merge(v[i],v[i-1]);
    v[n-1].f+=v[n-1].s;
    v[n-1].f%=v[n-1].s;
    cout<<v[n-1].f<<'\n';
}
int32_t main(){
    fastio
    int t;cin>>t;
    while(t--)solve();
}
/*
note:
bezout coeff
ax+by=gcd(a,b)
{x,y} for the kth -> {x+k(b/gcd(a,b)),y+k(a/gcd(a,b))}

CRT
weak:
unique solution to product of all m
merging m1,m2;
m1 and m2 are coprime
x=a mod m1, x=b mod m2
bezout coeff:
pm1+pm2=1
ans=bpm2+apm1
ans = a mod m1,ans = b mod m2
ans is unqiue to mod m1*m2;
ans = ans mod m1m2
then keep merging
*/