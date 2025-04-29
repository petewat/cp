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
const int mod=1e9+7,mxn=1e6+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,x,q,T,y;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
int mode=1;

struct line{
	double m,c;
	mutable double p;
	int get(int x) const{return (m*x)+c;}
	bool operator<(line a)const{
		if(mode)return m>a.m;
		else return p<a.p;
	}
};
double get(double m,double a,double b){
    double diff=b-a;
    return diff*sqrt(1+m*m);
}
double getdist(pair<double,double> a,pair<double,double> b){
    return sqrt((a.f-b.f)*(a.f-b.f)+(a.s-b.s)*(a.s-b.s));
}
double intersect(line a,line b){
    return (a.c-b.c)*1.0/(b.m-a.m);
}
vector<pii>have[mxn+10];
int suf[mxn+10],MX=1e6;
struct fen{
    int fwk[mxn+10];
    void update(int pos,int val){
        for(int i=pos;i<=MX;i+=(i&-i))fwk[i]+=val;
    }
    int qry(int pos){
        int sum=0;
        for(int i=pos;i>0;i-=(i&-i))sum+=fwk[i];
        return sum;
    }
}t;
int32_t main(){
    fastio
	cin>>n>>T;
    cin>>x>>y;
    vector<pair<int,pii>>v;
    for(int i=0;i<n;i++){
        int a,b,c;cin>>a>>b>>c;
        v.pb({a,{b,c}});
    }
    int cur=0;
    vector<line>have;
    vector<pii>have2;
    for(int i=0;i<T;i++){
        while(cur<v.size()&&v[cur].f<=i){
            line x;
            x.m=-v[cur].s.s*1.0/v[cur].s.f;
            x.c=v[cur].s.s;
            for(int j=0;j<cur;j++)if(intersect(x,have[j])<0){
                t.update(min(v[j].s.f,v[cur].s.f)+1,max(v[j].s.f,v[cur].s.f)-1);
            }
            have.pb(x);
            have2.pb(v[cur].s);
            cur++;
        }
        sort(all(have2));
        int bound=y,ans=inf;
        for(int j=have2.size()-1;j>=0;j--){
            if(t.qry(have2[j].f)==0){
                ans=min(ans,(int)(getdist({x,0},{have2[j].f,0})+getdist({have2[j].f,0},{0,bound})+getdist({0,bound},{0,y})));
            }
            bound=min(bound,have2[j].s);
        }
        cout<<ans<<'\n';
    }
}
/*
*/