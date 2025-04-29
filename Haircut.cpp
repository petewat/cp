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
#define double long double
using namespace std;
const int mod=998244353,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
struct fen{
	int fwk[mxn+10];
    void update(int pos,int val){
        for(int i=pos;i<=n;i+=(i&-i))fwk[i]+=val;
    }
    int qry(int pos){
        int sum=0;
        for(int i=pos;i>0;i-=(i&-i))sum+=fwk[i];
        return sum;
    }
}t;
int A[mxn+10];
vector<int>have[mxn+10];
int32_t main(){
	fastio
    setIO("haircut");
    cin>>n;
    for(int i=1;i<=n;i++)cin>>A[i],have[A[i]].pb(i);
    for(int i=1;i<=n;i++)t.update(i,1);
    int inv=0;
    for(int i=0;i<n;i++){
        cout<<inv<<'\n';
        for(auto j:have[i])t.update(j,-1);
        for(auto j:have[i])inv+=t.qry(j);
    }
}

/*

*/