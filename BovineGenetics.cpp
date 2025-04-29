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
#define int long long
#define double long double
using namespace std;
using cd = complex<double>;
double const PI=acos(-1);
const int mod=1e9+7,mxn=1e5+5,inf=1e18,minf=-1e18,lg=27,Mxn=lg*mxn;
//#undef int
int k,m,n,q,d;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);	
	freopen((name+".out").c_str(),"w",stdout);	
}
int dp[mxn+10][4][4][4];
void add(int &x,int y){x=(x+y+mod)%mod;}
int get(char x){
    if(x=='A')return 0;
    if(x=='G')return 1;
    if(x=='C')return 2;
    if(x=='T')return 3;
    return 4;
}
int32_t main(){
	fastio
    string a;cin>>a;
    n=a.size();
    for(int i=0;i<4;i++){
        if(a[0]=='?')for(int j=0;j<4;j++)dp[1][i][j][j]=1;
        else dp[1][i][get(a[0])][get(a[0])]=1;
    }
    for(int i=1;i<=n;i++){
        for(int need=0;need<4;need++){
            for(int nxt=0;nxt<4;nxt++){
                //continue
                int sum=0;
                for(int cur=0;cur<4;cur++)add(sum,dp[i-1][need][nxt][cur]);
                if(a[i-1]!='?'){
                    add(dp[i][need][nxt][get(a[i-1])],(sum-dp[i-1][need][nxt][get(a[i-1])]+mod)%mod);
                }
                else{
                    for(int cur=0;cur<4;cur++)add(dp[i][need][nxt][cur],(sum-dp[i-1][need][nxt][cur]+mod)%mod);
                }
                //finish
                if(a[i]!='?'){
                    add(dp[i+1][nxt][get(a[i])][get(a[i])],dp[i][need][nxt][need]);
                }
                else{
                    for(int g=0;g<4;g++)add(dp[i+1][nxt][g][g],dp[i][need][nxt][need]);
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)add(ans,dp[n][i][j][i]);
    cout<<ans;
}
/*



*/