#include "abc.h"
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
#include <cstdlib> 
#include <cstdint>
using namespace std;
#define all(x) x.begin(),x.end()
#define pb push_back
#define f first
#define s second
// you may find the definitions useful
const int OP_ZERO    = 0;  // f(OP_ZERO,    x0, x1) = 0
const int OP_NOR     = 1;  // f(OP_NOR,     x0, x1) = !(x0 || x1)
const int OP_GREATER = 2;  // f(OP_GREATER, x0, x1) = (x0 > x1)
const int OP_NOT_X1  = 3;  // f(OP_NOT_X1,  x0, x1) = !x1
const int OP_LESS    = 4;  // f(OP_LESS,    x0, x1) = (x0 < x1)
const int OP_NOT_X0  = 5;  // f(OP_NOT_X0,  x0, x1) = !x0
const int OP_XOR     = 6;  // f(OP_XOR,     x0, x1) = (x0 ^ x1)
const int OP_NAND    = 7;  // f(OP_NAND,    x0, x1) = !(x0 && x1)
const int OP_AND     = 8;  // f(OP_AND,     x0, x1) = (x0 && x1)
const int OP_EQUAL   = 9;  // f(OP_EQUAL,   x0, x1) = (x0 == x1)
const int OP_X0      = 10; // f(OP_X0,      x0, x1) = x0
const int OP_GEQ     = 11; // f(OP_GEQ,     x0, x1) = (x0 >= x1)
const int OP_X1      = 12; // f(OP_X1,      x0, x1) = x1
const int OP_LEQ     = 13; // f(OP_LEQ,     x0, x1) = (x0 <= x1)
const int OP_OR      = 14; // f(OP_OR,      x0, x1) = (x0 || x1)
const int OP_ONE     = 15; // f(OP_ONE,     x0, x1) = 1

// Alice
int // returns la
alice(
    /*  in */ const int n,
    /*  in */ const char names[][5],
    /*  in */ const unsigned short numbers[],
    /* out */ bool outputs_alice[]
){
    //since everything will appear in bobß we can just sor and label 0->n
    map<string,int>mp;
    for(int i=0;i<n;i++){
        string a="";
        for(int j=0;j<5;j++)a=(a+names[i][j]);
        mp[a]=numbers[i];
    }
    //if(mp.size()>1)assert(0);
    int st=0;
    for(auto i:mp){
        for(int j=0;j<16;j++){
            if(i.s&(1<<j))outputs_alice[st]=1;
            else outputs_alice[st]=0;
            st++;
        }
    }
    //if(st!=16*n)assert(0);
    return 16*n;
}
// Bob
int // returns lb
bob(
    /*  in */ const int m,
    /*  in */ const char senders[][5],
    /*  in */ const char recipients[][5],
    /* out */ bool outputs_bob[]
) {
    map<string,int>mp;
    for(int i=0;i<m;i++){
        string a="";
        for(int j=0;j<5;j++)a=(a+senders[i][j]);
        mp[a]=1;
    }
    for(int i=0;i<m;i++){
        string a="";
        for(int j=0;j<5;j++)a=(a+recipients[i][j]);
        mp[a]=1;
    }
    int cnt=0;
    for(auto &i:mp)i.s=cnt++;
    int id=0;
    for(int i=0;i<m;i++){
        string a="";
        for(int j=0;j<5;j++)a=(a+senders[i][j]);
        int x=mp[a];
        for(int j=0;j<6;j++){
            if(x&(1<<j))outputs_bob[id]=1;
            else outputs_bob[id]=0;
            id++;
        }
        a="";
        for(int j=0;j<5;j++)a=(a+recipients[i][j]);
        x=mp[a];
        for(int j=0;j<6;j++){
            if(x&(1<<j))outputs_bob[id]=1;
            else outputs_bob[id]=0;
            id++;
        }
    }
    //if(id!=(6*2*m))assert(0);
    return id;
}
// Circuit
int // returns l
circuit(
    /*  in */ const int la,
    /*  in */ const int lb,
    /* out */ int operations[],
    /* out */ int operands[][2],
    /* out */ int outputs_circuit[][16]
) {
    //test
    int id=la+lb;
    int n=la/(16),m=lb/12;
    for(int j=0;j<n;j++)for(int i=0;i<16;i++)outputs_circuit[j][i]=-1;
    auto add=[&](int a,int b,int x){
        operations[id]=x;
        operands[id][0]=a,operands[id][1]=b;
        id++;
        return id-1;
    };
    auto actualadd=[&](int pos,int x,int who){//adding to "x" to bit "pos" of "who"
        int last=x;
        for(int k=pos;k<16;k++){
            if(outputs_circuit[who][k]==-1){
                outputs_circuit[who][k]=last;
                break;
            }
            int nx=add(last,outputs_circuit[who][k],OP_AND);
            outputs_circuit[who][k]=add(outputs_circuit[who][k],last,OP_XOR);
            last=nx;
        }
    };
    int zero=-1,one=-1;
    for(int i=0;i<12;i++){
        if(zero==-1)zero=i,one=i;
        else zero=add(zero,i,OP_AND),one=add(one,i,OP_OR);
    }
    //wtf 
    int st=la;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int x=-1;//check first number is j
            for(int g=0;g<6;g++){
                int y;
                if(j&(1<<g))y=add(one,st+g,OP_EQUAL);
                else y=add(zero,st+g,OP_EQUAL);
                if(x==-1)x=y;
                else x=add(x,y,OP_AND);
            }
            for(int k=0;k<n;k++){
                if(k==j)continue;
                int x2=-1;//check second number =k
                for(int g=0;g<6;g++){
                    int y2;
                    if(k&(1<<g))y2=add(one,st+6+g,OP_EQUAL);
                    else y2=add(zero,st+6+g,OP_EQUAL);
                    if(x2==-1)x2=y2;
                    else x2=add(x2,y2,OP_AND);
                }
                //x2&x then i&j is correct
                int tmp=add(x,x2,OP_AND);//valid?
                for(int g=0;g<16;g++){
                    int tmp2=add(tmp,(j*16)+g,OP_AND);//value
                    actualadd(g,tmp2,k);
                }
            }
        }
        st+=12;
    }
    for(int j=0;j<n;j++)for(int i=0;i<16;i++)if(outputs_circuit[j][i]==-1)outputs_circuit[j][i]=zero;
    cout<<id;
    return 0;
    //return id;
/*
1 1
a 100
a a
a a
*/

/*
g++ -c abc.cpp -o abc.o
g++ -c grader.cpp -o grader.o
g++ abc.o grader.o -o grader
./grader

2 2
a 1
b 1
a b
b a


2 1
a 100
b 200
b a

3 5
alic 10000
bob 20000
circ 30000
alic circ
bob circ
bob alic
circ circ
circ circ

*/
}
