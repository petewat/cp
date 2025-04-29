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
//#define ll long long
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
const int mod=998244353,mxn=3e5+5,inf=1e18,minf=-1e18,lg=62;
int32_t main(){
    int n;cin>>n;
    vector<pii>cord(n);
    for(auto &i:cord)cin>>i.f>>i.s;
    if(n==1)cout<<-1<<'\n';
    else if(n==2){
        int x=(abs(cord[0].f-cord[1].f)+1),y=(abs(cord[0].s-cord[1].s)+1);
        cout<<x*y-1<<'\n';
    }
}
/*
*/