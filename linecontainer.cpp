#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<limits.h>
#include <cassert>
#include <cstdint>
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric> //gcd(a,b)
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
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
#pragma GCC optimize ("03,unroll-loops")
using namespace std;
#define int long long
#define double long double
const int mod=1e5+7,mxn=1e6+5,lg=30,inf=1e18,minf=-1e18;
int mode=1;
int v[mxn+10];
struct line{
	int m,c;
	mutable int p;
	int get(int x) const{return (m*x)+c;}
	bool operator<(line a)const{
		if(mode)return m>a.m;//min convexhull
		else return p<a.p;
	}
};
struct cht{
	multiset<line>v;
	int div(int a,int b){return (a/b)-(!(a%b==0||(a*b)>=0));}
	int intersect(multiset<line>::iterator a,multiset<line>::iterator b){return div((a->c-b->c),(b->m-a->m));}
	void cal(multiset<line>::iterator a){a->p=((a==v.end())?inf:intersect(a,next(a)));}
	bool bad(multiset<line>::iterator a,multiset<line>::iterator b){
		if(b==v.end())return a->p=inf,0;
		if(a->m==b->m)a->p=(a->c<=b->c)?inf:minf;
		else a->p=intersect(a,b);
		return a->p>=b->p;
	}
	void add(line a){
		auto it=v.insert(a);
		while(bad(it,next(it)))v.erase(next(it));
		if(it!=v.begin()&&bad(prev(it),it))bad(prev(it),it=v.erase(it));
		if(it!=v.begin())it=prev(it);
		while(it!=v.begin()&&bad(prev(it),it)){
			bad(prev(it),it=v.erase(it));
			it=prev(it);
		}
	}
	int qry(int x){
		if(v.empty())return 0;
		mode=0;
		auto it=v.lb((line){0,0,x})->get(x);
		mode=1;
		return it;
	}
}t;
