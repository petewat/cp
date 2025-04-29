#include<bits/stdc++.h>
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
#define sz(x) (int)((x).size())
#define int long long
using namespace std;
const int mod=1e9+7,mxn=2e5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m,d,q,T;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);
}
int mode=1;
struct line{
    int m,c;
    mutable int p;
    int get(int x)const{return (x*m)+c;}
    bool operator<(line o)const{
        if(mode)return m>o.m;
        return p<o.p;
    }
};
struct cht{
    multiset<line>v;
    int div(int a,int b){
        if((!(a%b))||(a*b>=0))return a/b;
        return (a/b)-1;
    }
    int intersect(multiset<line>::iterator a,multiset<line>::iterator b){
        return div(a->c-b->c,b->m-a->m);
    }
    bool bad(multiset<line>::iterator a,multiset<line>::iterator b){
        if(b==v.end())return a->p=inf,0;
        if(a->m==b->m)a->p=((a->c<=b->c)?inf:minf);
        else a->p=intersect(a,b);
        return a->p>=b->p;
    }
    void add(line a){
        auto it=v.insert(a);
        while(it!=v.end()&&bad(it,next(it)))v.erase(next(it));
        if(it!=v.begin()&&bad(prev(it),it))bad(prev(it),it=v.erase(it));
        if(it!=v.begin())it=prev(it);
        while(it!=v.begin()&&bad(prev(it),it)){
            bad(prev(it),it=v.erase(it));
            it=prev(it);
        }
    }
    int qry(int x){
        mode=0;
        auto it=v.lb((line){0,0,x});
        mode=1;
        return it->get(x);
    }
}t;
int32_t main(){
	fastio
    cin>>n>>q;
    for(int i=0;i<n;i++){
        int a,b;cin>>a>>b;
        t.add((line){a,b});
    }
    while(q--){
        int x;cin>>x;
        if(x){
            int a;cin>>a;
            cout<<t.qry(a)<<'\n';
        }
        else{
            int a,b;cin>>a>>b;
            t.add((line){a,b});
        }
    }
}