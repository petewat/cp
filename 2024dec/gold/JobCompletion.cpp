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
const int mod=1e9+7,mxn=2e5+5,lg=30,inf=1e18,minf=-1e18;
int n;
bool cmp(pii a,pii b){return a.f+a.s<b.f+b.s;}
void solve(){
	cin>>n;
	vector<pii>v(n);
	for(auto &i:v)cin>>i.f>>i.s;
	/*
	if x+b2>a1 x+b1<a2
	a2-b1>a1-b2
	a2+b2>a1+b1
	sort by a+b
	*/
	sort(all(v),cmp);
	priority_queue<int>pq;
	int csum=0;
	for(auto i:v){
		if(i.f>=csum)pq.push(i.s),csum+=i.s;
		else if(!pq.empty()&&pq.top()>i.s){
			//swap place
			//a1+b1<a2+b2 and b1>b2 a1<a2 ->its ok to swap
			csum-=pq.top();
			csum+=i.s;
			pq.pop();
			pq.push(i.s);
		}
	}
	cout<<pq.size()<<'\n';
}
int32_t main(){
	fastio
	int t;cin>>t;
	while(t--)solve();
}
/*
*/
