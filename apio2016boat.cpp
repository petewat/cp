#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<unordered_map>
#include <queue>
#include<cstring>
#include<limits.h>
#include<numeric> //gcd(a,b)
#include<cmath>
#include<set>
#include<cassert>
#include<algorithm>
#include<bitset> 
#include<stack>
using namespace std;
#define ll long long
#define f first
#define endl "\n"
#define s second
#define pii pair<int,int>
#define pppiiii pair<pii,pii>
#define ppii pair<int,pii>
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
//#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#define int int64_t
const int mxn=1000+10,minf=-1e18,mod=1e9+7,inf=1e18,lg=30;
int dp[mxn+10][mxn+10],ncr[mxn+10][mxn+10],sum[mxn+10][mxn+10];
int ncr2[mxn+10][mxn+10],choose[mxn+10][mxn+10];
int fac[mxn+10];
int inv(int x){
	int ex=mod-2,ans=1;
	while(ex){
		if(ex&1)ans=(ans*x)%mod;
		x=(x*x)%mod;
		ex>>=1;
	}
	return ans;
}
int get(int i,int j){
	if(choose[i][j]!=-1)return choose[i][j];
	int sum=0;
	for(int k=2;k<=j;k++){
		int x=(ncr2[i][k]*(ncr[j-2][k-2]))%mod;
		if(x)sum=(sum+x)%mod;
		else break;
	}
	choose[i][j]=sum;
	return choose[i][j];
}
int32_t main(){
	fastio
	int n;cin>>n;
	vector<pii>v(n+1);
	vector<int>com;
	for(int i=1;i<=n;i++){
		cin>>v[i].f>>v[i].s;
		v[i].f--;
	}
	for(int i=1;i<=n;i++)com.pb(v[i].f),com.pb(v[i].s);
	sort(all(com));
	com.erase(unique(all(com)),com.end());
	/*
	ncr i,j->(i,j+1)
	x=(x*(len-j+1))*inv(j)
	*/
	ncr[0][0]=1;
	for(int i=1;i<=n;i++)for(int j=0;j<=n;j++){
		if(j)ncr[i][j]=(ncr[i-1][j]+ncr[i-1][j-1])%mod;
		else ncr[i][j]=ncr[i-1][j];
	}
	for(int i=1;i<com.size();i++){
		int len=com[i]-com[i-1];
		ncr2[i][1]=len;	
		for(int j=2;j<=min(n,len);j++)ncr2[i][j]=((ncr2[i][j-1]*(len-j+1))%mod*inv(j))%mod;
	}
	for(int i=1;i<com.size();i++)for(int j=2;j<=n;j++)choose[i][j]=-1;
	for(int i=1;i<com.size();i++)choose[i][1]=ncr2[i][1];
	for(int i=0;i<=2*n;i++)sum[0][i]=1;
	for(int i=0;i<=2*n;i++)sum[i][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<com.size();j++){
			if(com[j]>v[i].f&&com[j]<=v[i].s){
				if(choose[j][1]==1)dp[i][j]=sum[i-1][j-1];
				else{
					int cnt=0;
					for(int back=i;back>=1;back--){
						if(com[j]>v[back].f&&com[j]<=v[back].s){
							cnt++;
							dp[i][j]=(dp[i][j]+(sum[back-1][j-1]*get(j,cnt))%mod)%mod;
						}
					}
				}
			}
			sum[i][j]=((dp[i][j]+(sum[i-1][j]+sum[i][j-1])%mod)%mod-sum[i-1][j-1]+mod)%mod;
		}
	}
	cout<<(sum[n][com.size()-1]-1);
}
/*
*/
