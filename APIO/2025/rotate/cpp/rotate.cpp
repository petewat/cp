#include "rotate.h"
#include <vector>
#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define pb push_back
#define pii pair<int,int>
#define f first
#define s second
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native,sse,sse2,sse3")
#pragma GCC optimize("O3")
using namespace std;
int getcost(vector<int>x){
    int ans=0;
    for(int i=0;i<x.size();i++)for(int j=i+1;j<x.size();j++){
        ans+=min(abs(x[i]-x[j]),50000-abs(x[i]-x[j]));
    }
    return ans;
}
int getinflue(int pos,vector<int>x){
    int ans=0;
    for(int i=0;i<x.size();i++)ans+=min(abs(x[i]-x[pos]),50000-abs(x[i]-x[pos]));
    return ans;
}
const int mxn=2e5;
void energy(int n, vector<int> v){
    int ca=getcost(v);
    int k=5e4;
    while(1){
        int c=0;
        for(int i=0;i<n;i++){
            for(int j=15;j>=0;j--){
                int A=getinflue(i,v);
                v[i]=(v[i]+(1LL<<j))%k;
                int B=getinflue(i,v);
                if(B-A>0){
                    rotate({i},(1LL<<j)),c=1;
                    ca=getcost(v);
                }
                else v[i]=(v[i]-(1LL<<j)+k)%k;
            }
        }
        if(c==0)break;
    }
}
/*

10
15008
3575
4195
17714
13590
19299
11259
10649
7980
19166
*/