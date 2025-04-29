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
const int mxn=2e5,inf=1e18+1,minf=-1e9,mod=1e9+7;
int n;
int v[mxn+10];
int32_t main(){
	fastio
    cin>>n;
    for(int i=1;i<=n;i++)cin>>v[i],v[i]+=v[i-1];
    vector<pair<int,pii>>range;
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)range.pb({v[j]-v[i-1],{i,j}});
    sort(all(range));
    stack<int>st;
    for(int i=1;i<=n;i++){
        int ans=inf,last=inf;
        for(auto j:range){
            if(j.s.f>i||j.s.s<i){
                while(!st.empty())ans=min(ans,j.f-st.top()),st.pop();
                last=j.f;
            }
            else{
                if(last!=inf)ans=min(ans,j.f-last);
                st.push(j.f);
            }
        }
        cout<<ans<<'\n';
        while(!st.empty())st.pop();
    }

}
/*

*/