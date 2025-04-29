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
//#define int long long
#define double long double
using namespace std;
const int mod=1e9+7,mxn=2e3+5,inf=1e9,minf=-1e9,lg=30,Mxn=5e5;
//#undef int
int n,k,m,q;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
int mx[mxn+10][mxn+10];
int lab[mxn+10],c[2];
int32_t main(){
    fastio
    cin>>n;
    int yes=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++)cin>>mx[i][j];
    }
    for(int i=2;i<=n;i++)yes|=(mx[i-1][i]==2);
    if(yes){
        lab[1]=0;
        //if(mx[1][2]==1)lab[2]=1;
        c[0]=1;
        for(int i=2;i<=n;i++){
            if(mx[i-1][i]==2)lab[i]=lab[i-1];
            else lab[i]=lab[i-1]^1;
            /*
            else{
                if(mx[i-2][i]==2)lab[i]=lab[i-2];
                else lab[i]=3-lab[i-1]-lab[i-2];
            }*/
            c[lab[i]]++;
        }
        int mx=(c[1]>c[0]);
        for(int i=1;i<=n;i++)if(lab[i]==mx)cout<<i<<" ";
    }
    else{
        lab[1]=0;
        c[0]=1;
        for(int i=2;i<=n;i++){
            if(mx[i-1][i]==2)lab[i]=lab[i-1];
            else{
                if(mx[i-2][i]==2)lab[i]=lab[i-2];
                else lab[i]=3-lab[i-1]-lab[i-2];
            }
            c[lab[i]]++;
        }
        int mx=max({c[0],c[1],c[2]});
        for(int i=1;i<=n;i++)if(c[lab[i]]==mx)cout<<i<<" ";
    }
}