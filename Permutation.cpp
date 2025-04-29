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
#define int long long
using namespace std;
const int mod=1e9+7,mxn=2e5+5,inf=1e9,minf=-1e9,lg=30;
//#undef int
int n,k,m,q;
void setIO(string name){	
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
double err=1e-15;
int vis[42][42][42];
int X[42],Y[42];
double area(int x,int y,int z){
	double a=(X[x]*(Y[y]-Y[z]));
	double b=(X[y]*(Y[z]-Y[x]));
	double c=(X[z]*(Y[x]-Y[y]));
	return abs(a+b+c)*1.0/2;
}
bool inside(int x,int y,int z,int a){
	//check if a is inside tri x,y,z
	double A=area(x,y,z)-area(x,y,a)-area(x,a,z)-area(a,y,z);
	return (abs(A)<err);
}
int dp[42][42][42][42];
void add(int &x,int a){x=(x+a)%mod;}
void solve(int x,int y,int z){
	if(vis[x][y][z])return;
	vis[x][y][z]=1;
	int cnt=0;
	vector<int>have;
	for(int c=1;c<=n;c++)if(inside(x,y,z,c)){
		have.pb(c);
		cnt++;
	}
	dp[3][x][y][z]=6;
	int cx=x,cy=y,cz=z;
	for(auto i:have){
		if(i==x||i==y||i==z)continue;
		for(int k=0;k<3;k++){
			vector<int>ord={cx,cy,i};
			sort(all(ord));
			solve(ord[0],ord[1],ord[2]);
			for(int use=4;use<=cnt;use++){
				add(dp[use][x][y][z],dp[use-1][ord[0]][ord[1]][ord[2]]);
			}
			swap(cx,cz);
			swap(cy,cx);
		}
	}
	for(int use=4;use<=cnt;use++){
		add(dp[use][x][y][z],(dp[use-1][x][y][z]*(cnt-use+1))%mod);
	}
}
int32_t main(){
    fastio
	cin>>n;
	for(int i=1;i<=n;i++)cin>>X[i]>>Y[i];
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)for(int k=j+1;k<=n;k++){
		int yes=1;
		for(int c=1;c<=n;c++)if(c!=i&&c!=j&&c!=k)yes&=inside(i,j,k,c);
		if(yes){
			solve(i,j,k);
			cout<<dp[n][i][j][k];
			return 0;
		}
	}
	cout<<0;
}
/*
*/