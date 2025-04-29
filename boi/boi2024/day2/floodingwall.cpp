#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f first
#define s second
#define pii pair<int,int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize("O3")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native,sse,sse2,sse3")
#define sz(x) (int)((x).size())
#define int long long
using namespace std;

const int mod=1e9+7,mxn=1e6,inf=1e9,minf=-1e9,lg=30,Mxn=1e9;

int n,k,m,d,q;
int val[mxn+10][2];
int P[mxn+10],sub[mxn+10][2],sz;

vector<int>comp;
struct seg{
    int dp[4*mxn+10], waysx[4*mxn+10], ways[4*mxn+10];
    int lazy[4*mxn+10][2]; 
	inline void init(){for(int i=0;i<=4*sz;i++)dp[i]=waysx[i]=ways[i]=lazy[i][1]=0,lazy[i][0]=1;}

    inline void apply(int pos, pii x) {
        dp[pos] = (x.f * dp[pos] + x.s * waysx[pos]) % mod;
        waysx[pos] = (x.f * waysx[pos]) % mod;
        ways[pos] = (x.f * ways[pos]) % mod;
        lazy[pos][1] = (lazy[pos][1] * x.f + lazy[pos][0] * x.s) % mod;
		lazy[pos][0] = (lazy[pos][0] * x.f) % mod;
    }
 
    inline void push(int pos, int l, int r) {
        if (lazy[pos][0] == 1 && lazy[pos][1] == 0) return;
        if (l != r) {
            apply(pos<<1, {lazy[pos][0], lazy[pos][1]});
            apply(pos<<1|1, {lazy[pos][0], lazy[pos][1]});
        }
        lazy[pos][0] = 1;
        lazy[pos][1] = 0;
    }
 
    inline void pull(int pos){
        dp[pos] = (dp[pos<<1] + dp[pos<<1|1]) % mod;
        waysx[pos] = (waysx[pos<<1] + waysx[pos<<1|1]) % mod;
        ways[pos] = (ways[pos<<1] + ways[pos<<1|1]) % mod;
    }

	inline void update(int ql,int qr,int k,int pos=1,int l=0,int r=sz){
		if(l>qr||r<ql)return;
		if(ql<=l&&r<=qr)return void(apply(pos,{k,k}));
		push(pos,l,r);
		update(ql,qr,k,pos<<1,l,((l+r)>>1));
		update(ql,qr,k,pos<<1|1,((l+r)>>1)+1,r);
		pull(pos);
	}
	inline void modify(int qpos,int d,int w,int pos=1,int l=0,int r=sz){
		if(l>qpos||r<qpos)return;
		if(l==r){
			dp[pos]=(dp[pos]+d)%mod;
			ways[pos]=(ways[pos]+w)%mod;
			waysx[pos]=(waysx[pos]+(w*comp[l])%mod)%mod;
			return;
		}
		push(pos,l,r);
		if(qpos<=(l+r)>>1)modify(qpos,d,w,pos<<1,l,((l+r)>>1));
		else modify(qpos,d,w,pos<<1|1,((l+r)>>1)+1,r);
		pull(pos);
	}
    inline pii get(int ql, int qr, int pos=1, int l=0, int r=sz) {
        if (l > qr || r < ql) return {0,0};
        if (ql <= l && r <= qr) return {ways[pos],dp[pos]};
        push(pos, l, r);
        int m = (l + r) >> 1;
		pii a=get(ql,qr,pos<<1,l,m);
		pii b=get(ql,qr,pos<<1|1,m+1,r);
		return {(a.f+b.f)%mod,(a.s+b.s)%mod};
    }
}t;


int pref[mxn+10],suf[mxn+10];
struct fen{
	int fwk[mxn+10];
	inline void init(){for(int i=0;i<=sz+1;i++)fwk[i]=0;}
	inline void update(int pos,int val){
		pos++;
		if(pos<=0)return;
		for(int i=pos;i<=sz+1;i+=(i&-i))fwk[i]+=val;
	}
	inline int qry(int pos){
		pos++;
		int sum=0;
		if(pos<=0)return 0;
		for(int i=pos;i>0;i-=(i&-i))sum+=fwk[i];
		return sum;
	}
}tmx;
pii upd[2];
int32_t main(){
	fastio
	cin>>n;
	int ans=0;
	P[0]=1;
	comp.pb(0);
	for(int i=1;i<=n;i++)P[i]=(P[i-1]*2LL)%mod;
	for(int i=1;i<=n;i++)cin>>val[i][0];
	for(int i=1;i<=n;i++){
		cin>>val[i][1];
		if(val[i][0]>val[i][1])swap(val[i][0],val[i][1]);
		comp.pb(val[i][0]);
		comp.pb(val[i][1]);
	}
	sort(all(comp));
	comp.erase(unique(all(comp)),comp.end());
	sz=comp.size()-1;
	for(int i=1;i<=n;i++){
		val[i][0]=lb(all(comp),val[i][0])-comp.begin();
		val[i][1]=lb(all(comp),val[i][1])-comp.begin();
	}

	for(int i=1;i<=n;i++){
		for(int k=0;k<2;k++)ans=(ans-(P[n-1]*comp[val[i][k]])%mod+mod)%mod;
	}

	int sum2=0;

	t.init();
	t.modify(0,0,1);

	for(int i=1;i<=n;i++)tmx.update(val[i][1],1);
	suf[n+1]=minf;
	pref[0]=minf;
	for(int i=n;i>=1;i--)suf[i]=max(suf[i+1],val[i][0]);
	for(int i=1;i<=n;i++)pref[i]=max(pref[i-1],val[i][0]);
    pii x;
	for(int i=1;i<=n;i++){
		tmx.update(val[i][1],-1);
		for(int k=0;k<2;k++){
            if (suf[i+1] <= val[i][k]-1) {
                sum2 = P[tmx.qry(val[i][k]-1)];
				x=t.get(0,val[i][k]);
				int sum = (x.s + x.f * comp[val[i][k]]) % mod;
                ans = (ans + sum2 * sum) % mod;
                sub[i][k]=sum2;
            }
			x=t.get(0,val[i][k]-1);
			upd[k]={x.s, x.f};
		}
		t.update(0,val[i][0]-1,0);
		t.update(val[i][0],val[i][1]-1,1);
		t.update(val[i][1],sz,2);
		for(int k=0;k<2;k++){
			t.modify(val[i][k],(upd[k].f+(comp[val[i][k]]*upd[k].s)%mod)%mod,upd[k].s);
		}
	}
	for(int i=1;i<=n;i++)tmx.update(val[i][1],1);

	t.init();
	t.modify(0,0,1);
	for(int i=n;i>=1;i--){
		//fix left equal
		tmx.update(val[i][1],-1);
        for (int k = 0; k < 2; k++){
			x=t.get(0,val[i][k]-1);
            if (pref[i-1]<=val[i][k]){
                sum2 = P[tmx.qry(val[i][k])];
                int sum = (x.s + x.f * comp[val[i][k]]) % mod;
                ans = (ans + sum2 * sum) % mod;
                ans = (ans - sub[i][k] * sum2 % mod * comp[val[i][k]] % mod + mod) % mod;
            }
			upd[k] = {x.s, x.f};
        }

		t.update(0,val[i][0]-1,0);
		t.update(val[i][0],val[i][1]-1,1);
		t.update(val[i][1],sz,2);
		for(int k=0;k<2;k++){
			t.modify(val[i][k],(upd[k].f+(comp[val[i][k]]*upd[k].s)%mod)%mod,upd[k].s);
		}
	}
	cout<<ans;
}
/*
*/