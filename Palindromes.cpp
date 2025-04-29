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
//#define int long long
#define double long double
const int mxn=7500,inf=1e9,minf=-1e9;
int n;
int32_t main(){
	fastio
	string a;cin>>a;
	n=a.size();
	ll ans=0;
	vector<int>have;
	for(int i=0;i<n;i++)if(a[i]=='G')have.pb(i);
	for(int lcen=0;lcen<have.size();lcen++)for(int rcen=lcen;rcen<have.size()&&rcen<=lcen+1;rcen++){
		int l=lcen,r=rcen;
		vector<int>cnt(2*n+1,0);
		int add=0,F=0;
		while(l>=0&&r<have.size()){
			int leftgap=have[l],rightgap;
			if(l)leftgap-=have[l-1];
			else leftgap++;
			if(r+1<have.size())rightgap=have[r+1];
			else rightgap=n;
			rightgap=rightgap-have[r];
			leftgap=have[l]-leftgap;
			rightgap=have[r]+rightgap;
			if(l!=r)cnt[have[l]+have[r]]+=2,add++;
			for(int cl=have[l];cl>leftgap;cl--){
				int t1=F,t2=add;
				for(int cr=have[r];cr<rightgap;cr++){
					if(lcen==rcen){
						if((cr-cl+1)%2)ans+=abs(have[lcen]-((cr+cl)/2))+F;
						else ans--;
					}
					else ans+=F;
					F+=add;
					add+=cnt[cl+cr+1];
				}
				F=t1,add=t2;
				add-=cnt[cl+have[r]];
				F-=add;
				//reset and move back
			}
			for(int cr=have[r];cr<rightgap;cr++){
				F+=add;
				add+=cnt[leftgap+cr+1];
			}
			l--,r++;
		}
	}
	cout<<ans;
}
/*
dp[i][j]=dp[i-1][j+1]

fix a,b
cost of chaning a <-> b when a,b are palindrome pair
a,b are palindrome iff  #1 to the left of a=#1 to the right of b
*/