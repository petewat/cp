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
#include<complex>
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
using cd = complex<double>;
double const PI=acos(-1);
const int mod=998244353,mxn=1e6+5,inf=1e9,minf=-1e9,lg=30;
//#undef int
int k,m,n,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int ans=0,cnt[mxn+10];
struct fen{
    int fwk[mxn+10];
    void update(int pos,int val){
        pos++;
        for(int i=pos;i<=n;i+=(i&-i))fwk[i]+=val;
    }
    int qry(int pos){
        pos++;
        if(pos<=0)return 0;
        int sum=0;
        for(int i=pos;i>0;i-=(i&-i))sum+=fwk[i];
        return sum;
    }
}t;
int get(int x){
    return t.qry(x)-t.qry(x-1);
}
int32_t main(){
	fastio
    cin>>n>>k;
    string a,b;cin>>a>>b;
    int sz=0;
    char what='?';
    for(int i=1;i<=n;i++){
        ans+=get(i%k);
        if(a[i-1]==b[i-1]){
            continue;
        }
        if(!sz)what=a[i-1];
        if(what==a[i-1]){
            sz++,t.update(i%k,1);
        }
        else{
            int x=k;
            int l=i%k,r=k-1;
            while(l<=r){
                int mid=l+(r-l)/2;
                if(t.qry(mid)-t.qry(i%k-1))x=min(x,mid),r=mid-1;
                else l=mid+1;
            }
            if(x==k){
                l=0,r=i%k;
                while(l<=r){
                    int mid=l+(r-l)/2;
                    if(t.qry(mid))x=min(x,mid),r=mid-1;
                    else l=mid+1;
                }
            }
            if(i%k!=x)ans++;
            sz--;
            t.update(x,-1);
        }
        
    }
    cout<<ans;
}
/*

*/