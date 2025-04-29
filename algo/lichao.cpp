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
#define sz(x) (int)((x).size())
#define int long long
using namespace std;
const int mod=1e9+7,mxn=4e7,inf=4e18,minf=-4e18,lg=30;
//#undef int
int n,k,m,d,q,T;
void setIO(string name){
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);
}
struct line{
	int m,c;
	int get(int x){return (x*m)+c;}
	line():c(inf){};
	line(int a,int b):m(a),c(b){};
};
struct lichao{
	line v[mxn+10];
	int32_t L[mxn+10],R[mxn+10];
	int32_t T=1;

	void addline(int32_t ql,int32_t qr,line a,int32_t pos=1,int32_t l=-1e9,int32_t r=1e9){
		int mid=l+(r-l)/2;
		bool BL=a.get(l)<v[pos].get(l);
		bool BM=a.get(mid)<v[pos].get(mid);
		if(BM)swap(a,v[pos]);
		if(l==r)return;
		if(BL^BM){
			if(!L[pos])L[pos]=++T;
			addline(ql,qr,a,L[pos],l,mid);
		}
		else{
			if(!R[pos])R[pos]=++T;
			addline(ql,qr,a,R[pos],mid+1,r);
		}
	}
	void update(int32_t ql,int32_t qr,line a,int32_t pos=1,int32_t l=-1e9,int32_t r=1e9){
		if(l>qr||r<ql)return;
		if(ql<=l&&r<=qr)return void(addline(ql,qr,a,pos,l,r));
		int mid=l+(r-l)/2;
		if(!L[pos])L[pos]=++T;
		if(!R[pos])R[pos]=++T;
		update(ql,qr,a,L[pos],l,mid);
		update(ql,qr,a,R[pos],mid+1,r);
	}
	int qry(int32_t qpos,int32_t pos=1,int32_t l=-1e9,int32_t r=1e9){
		if(pos==0)return inf;
		if(l>qpos||r<qpos)return inf;
		int mid=l+(r-l)/2;
		if(l<=qpos&&qpos<=r){
			if(qpos<=mid)return min(v[pos].get(qpos),qry(qpos,L[pos],l,mid));
			return min(v[pos].get(qpos),qry(qpos,R[pos],mid+1,r));
		}
		return min(qry(qpos,L[pos],l,mid),qry(qpos,R[pos],mid+1,r));
	}
}t;
int32_t main(){
	fastio
	int n,q;cin>>n>>q;
	for(int i=0;i<n;i++){
		int l,r,a,b;cin>>l>>r>>a>>b;
		r--;
		t.update(l,r,(line){a,b});
	}
	while(q--){
		int x;cin>>x;
		if(x){
			int a;cin>>a;
			int x=t.qry(a);
			if(x>=inf)cout<<"INFINITY\n";
			else cout<<x<<'\n';
		}
		else{
			int l,r,a,b;cin>>l>>r>>a>>b;
			r--;
			t.update(l,r,(line){a,b});
		}
	}

}