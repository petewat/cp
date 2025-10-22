#include "train.h"
#include<iostream>
#include <vector>
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
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric> //gcd(a,b)
#include<bitset>
#include <cstdlib> 
#include <cstdint>
using namespace std;
#define ll long long
#define f first
//#define endl "\n"
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
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define ll long long
#define int long long
const ll mxn=1e5,inf=1e18;
struct edge{
    int x,y,a,b,c;
    bool operator<(edge p)const{return a<p.a;};
};
bool intersect(pii a,pii b){
    if(b.f<=a.f&&a.f<=b.s)return 1;
    if(b.f<=a.s&&a.s<=b.s)return 1;
    swap(a,b);
    if(b.f<=a.f&&a.f<=b.s)return 1;
    if(b.f<=a.s&&a.s<=b.s)return 1;
    return 0;
}
long long solve(int32_t n, int32_t m,int32_t w,vector<int32_t> T, std::vector<int32_t> X, std::vector<int32_t> Y,vector<int32_t> A, std::vector<int32_t> B, std::vector<int32_t> C, std::vector<int32_t> L,vector<int32_t> R) {
    vector<int>dist(n+1,inf);
    dist[0]=0;
    vector<edge>e;
    for(int i=0;i<m;i++)e.pb({X[i],Y[i],A[i],B[i],C[i]});
    sort(all(e));
    priority_queue<pair<pii,pii>,vector<pair<pii,pii>>,greater<pair<pii,pii>>>pq;
    //time node cost
    vector<pii>meal;
    for(int i=0;i<w;i++)meal.pb({L[i],R[i]});
    sort(all(meal));
    int curmeal=0;
    for(auto i:e){
        while(curmeal<meal.size()&&i.a>meal[curmeal].s)curmeal++;
        bool in=0;
        while(!pq.empty()&&pq.top().f.f<=i.a){
            int x=pq.top().s.f;
            if(curmeal<meal.size())in=!intersect(meal[curmeal],{pq.top().f.s,pq.top().f.f});
            else in=1;
            dist[x]=min(dist[x],pq.top().s.s-(T[x]*(curmeal-in+1)));
            //if this is also in then we want to take the current one
            pq.pop();
        }
        if(curmeal<meal.size())in=intersect(meal[curmeal],{i.a,i.b});
        else in=1;
        //if this is in then we dont have to take the current one
        //so just add curmeal-1
        pq.push({{i.b,i.a},{i.y,dist[i.x]+i.c+(T[i.x]*(curmeal-in+1))}});
    }
    bool in=0;
    while(!pq.empty()){
        while(curmeal<meal.size()&&pq.top().f.f<=meal[curmeal].f)curmeal++;
        int x=pq.top().s.f;
        dist[x]=min(dist[x],pq.top().s.s-(T[x]*(curmeal)));
        pq.pop();
    }
    for(int i=0;i<n;i++)dist[i]+=(T[i]*(curmeal));
    if(dist[n-1]>=inf)return -1;
    return dist[n-1];
}

/*



*/