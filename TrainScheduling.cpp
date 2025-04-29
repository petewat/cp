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
const int mod=1e9+7,mxn=1e4+5,lg=30,inf=1e18,minf=-1e18;
int n;
/*
*/
int32_t main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>v[i].f>>v[i].s;
	sort(v+1,v+1+n);
	int ans=0;
	stack<int>st,st2;
	v[0].s=inf;
	for(int i=1;i<=n;i++){
		while(!st.empty()&&v[st.top()].s<v[i].s)st.pop();
		while(!st2.empty()&&v[st2.top()].s>=v[i].s)st2.pop();
		if(!st.empty()){
			go[i][0]=st.top();
			for(int j=1;j<=lg;j++)go[i][j]=go[go[i][j-1]][j-1];
		}
		if(!st2.empty()){
			int g=1;
			ans++;
			int c1=st2.top();
			for(int k=lg;k>=0;k--)if(v[go[c1][k]].s<v[i].s){
				ans+=(1LL<<k);
				g+=(1LL<<k);
				c1=go[c1][k];
			}
			cout<<g<<" "<<v[i].f<<"HUH\n";
		}
		st.push(i);
		st2.push(i);
	}
	cout<<ans;
}