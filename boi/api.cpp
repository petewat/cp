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
using namespace std;
const int mod=1e9+7,mxn=2e5+5,inf=1e9,minf=-1e9,lg=30,valbound=1e9;

using namespace std;

#define MAX_N 500
int vis[505],cur=0,n,dist[505][505];
int can[505][505],robber[505][505];
// modify the following functions
// you can define global variables and functions
void bfs(int root){
    queue<int>q;
    q.push(root);
    for(int i=0;i<n;i++)vis[i]=0;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        if(vis[cur])continue;
        vis[cur]=1;
        for(int i=0;i<n;i++)if(!vis[i]&&can[cur][i]){
            dist[root][i]=dist[root][cur]+1;
            q.push(i);
        }
    }
}
int start(int N, bool A[MAX_N][MAX_N]){
    n=N;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)can[i][j]=A[i][j];
    for(int i=0;i<n;i++)bfs(i);
    for(int i=0;i<n;i++)vis[i]=0;
    vis[0]=1;
    return 0;
}
int nextMove(int R){
    int go=-1;
    for(int i=0;i<n;i++)if(can[cur][i]&&!vis[i]){
        if(go==-1)go=i;
        if(dist[i][R]<dist[go][R])go=i;
    }
    //if(go==-1)return cur;
    //vis[go]=1;
    cur=go;
    return go;
}
// don't modify the main function
int main() {
    int N;
    cin >> N;
    bool A[MAX_N][MAX_N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
        }
    }
    int P = start(N,A);
    cout << P << endl;
    int R;
    cin >> R;
    while (true) {
        if (P == R) break;
        P = nextMove(R);
        cout << P << endl;
        if (P == R) break;
        cin >> R;
    }
}
