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
//#define int long long
//#define double long double
using namespace std;
using cd = complex<double>;
double const PI=acos(-1);
const int mod=1e9+7,mxn=1e5+5,inf=1e18,minf=-1e18,lg=15,base=311;
//#undef int
int k,m,n,q,d;
void setIO(string name){
    ios_base::sync_with_stdio(0); cin.tie(0);       
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}
//https://open.kattis.com/submissions/16815979
//and also cses problem
struct pt{int x,y;};
pt vec(pt x,pt y){
    //x-y;
    return {y.x-x.x,y.y-x.y};
}
int cross(pt a,pt b){
    //det of 2x2 vector, change a,b from pt to vector origin at c
    return (a.x*b.y)-(a.y*b.x);
}
//if axb is neg then b on the left of a (c is the centered pt)
bool left(pt a,pt b,pt c,bool collin){
    int o=cross(vec(c,a),vec(c,b));
    return o<0 ||(collin&&o==0);
}
bool right(pt a,pt b,pt c,bool collin){
    int o=cross(vec(c,a),vec(c,b));
    return o>0||(collin&&o==0);
}
bool cmp(pt a,pt b){
    if(a.x!=b.x)return a.x<b.x;
    return a.y<b.y;
}
void convexhull(vector<pt>&v,bool collin=false){
    //do we consider collinear pt?
    sort(all(v),cmp);
    //first and last pt
    pt p1=v[0],p2=v.back();
    vector<pt>up,down;
    //the upper and lower half
    up.pb(p1);
    down.pb(p1);
    for(int i=1;i<v.size();i++){
        if(i==v.size()-1||left(p1,v[i],p2,collin)){
            while(up.size()>1&&!left(up[up.size()-2],up.back(),v[i],collin))up.pop_back();
            up.pb(v[i]);
        }
        if(i==v.size()-1||right(p1,v[i],p2,collin)){
            while(down.size()>1&&!right(down[down.size()-2],down.back(),v[i],collin))down.pop_back();
            down.pb(v[i]);
        }
    }
    if(collin&&up.size()==v.size())return;
    v.clear();
    for(auto i:down)v.pb(i);
    for(int i=up.size()-2;i>0;i--)v.pb(up[i]);
}
int sign(int x){
    if(x<0)return -1;
    if(x==0)return 0;
    return 1;
}
double dist(pt a,pt b){
    return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int vis[mxn+10];
int32_t main(){
    fastio
    cin>>n;
    vector<pt>v(n);
    for(auto &i:v)cin>>i.x>>i.y;
    //get convex hull
    convexhull(v,0);
    //rotating calipers tech
    double ans=minf;
    cout<<fixed<<setprecision(10);
    if(v.size()==2)return cout<<dist(v[0],v[1])<<'\n',0;
    auto getnxt=[&](int x){return (x+1)%v.size();};
    auto getlast=[&](int x){return (x-1+v.size())%v.size();};
    int p2=0,p1=0;
    //get all anti podal pair
    vector<pii>anti_podal;
    for(;p1<v.size();p1++){
        pt e=vec(v[p1],v[getnxt(p1)]);
        while(p1==p2||p2==getnxt(p1)||(sign(cross(e,vec(v[getlast(p2)],v[p2])))==sign(cross(e,vec(v[p2],v[getnxt(p2)]))))){
            p2=getnxt(p2);
        }
        if(vis[p1])continue;
        vis[p1]=1;
        anti_podal.pb({p1,p2});
        anti_podal.pb({getnxt(p1),p2});
        if(cross(e,vec(v[p2],v[getnxt(p2)]))==0){
            anti_podal.pb({p1,getnxt(p2)});
            anti_podal.pb({getnxt(p1),getnxt(p2)});
            vis[p2]=1;
        }
    }
    for(auto i:anti_podal)ans=max(ans,dist(v[i.f],v[i.s]));
    cout<<ans;
}
/*

*/