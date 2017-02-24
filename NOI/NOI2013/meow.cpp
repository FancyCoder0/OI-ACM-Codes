/*
    Problem:
    Algorithm:
    Note:
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<vector>
#include<map>
#include<string>
#include<iomanip>
#include<iostream>
#include<cmath>
#include<queue>
#include<complex>
#include<ctime>
using namespace std;
 
#define rep(i,x,y) for(i=x;i<=y;i++)
#define _rep(i,x,y) for(i=x;i>=y;i--)
#define CL(S,x) memset(S,x,sizeof(S))
#define CP(S1,S2) memcpy(S1,S2,sizeof(S2))
#define ALL(x,S) for(x=S.begin();x!=S.end();x++)
#define sqr(x) ((x)*(x))
#define mp make_pair
#define fi first
#define se second
#define upmin(x,y) x=min(x,y)
#define upmax(x,y) x=max(x,y)
 
typedef long long ll;
typedef long double ld;
void read(int&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
char getc(){char c;for(c=getchar();c<=32;c=getchar());return c;}
 
const int N=100010;
int n,d,mod,i,j,k,l,p,x,t;
char a[N][101];
char c[N],r[N],o[N],sum;
 
int solve()
{
    int i,j,k,x,tmp;
    sum=0;rep(i,1,n)o[i]=rand()%mod,sum=(sum+o[i])%mod;
     
    if(mod==2)
{
    rep(i,0,d-1)
    {
        x=0;
        rep(j,1,n)
        x=(x+o[j]*a[j][i])&1;
        c[i]=x;
    }
    rep(i,1,n)
    {
        tmp=0;rep(j,0,d-1)tmp=(tmp+c[j]*a[i][j])&1;
        x=0;rep(j,0,d-1)x=(x+a[i][j]*a[i][j])&1;
        x=((sum-o[i]+x*o[i])&1+1)&1;
        if(tmp!=x)return i;
    }
}
    else
    {
        rep(i,0,d-1)
        rep(j,0,d-1)
        {
            x=0;
            rep(k,1,n)
            x=(x+o[k]*a[k][i]*a[k][j])%3;
            c[i*d+j]=x;
        }
        rep(i,1,n)
        {
            tmp=0;rep(j,0,d-1)rep(k,0,d-1)tmp=(tmp+c[j*d+k]*a[i][j]*a[i][k])% 3;
            x=0;rep(j,0,d-1)rep(k,0,d-1)x=(x+a[i][j]*a[i][k]*a[i][j]*a[i][k])% 3;
            x=(((sum-o[i]+x*o[i])% 3)+3)%3;
            if(tmp!=x)return i;
        }
    }
    return 0;
}

bool pr(int i)
{
    if(i==0)return 0;
    int j,k,x;
    rep(j,1,n)if(i!=j)
    {
        x=0;
        rep(k,0,d-1)x=(x+a[i][k]*a[j][k])%mod;
        if(x==0){if(i>j)swap(i,j);printf("%d %d\n",i,j);return 1;}
    }
    return 0;
}
int main()
{
    //freopen("meow.in","r",stdin);
    //freopen("meow.out","w",stdout);
    
    srand(1111);
    read(n);read(d);read(mod);
    rep(i,1,n)rep(j,0,d-1)read(x),a[i][j]=x%mod;

     
    rep(i,1,5)if(pr(solve()))break;
    if(i>5)printf("-1 -1\n");
    
    scanf("\n");
    return 0;
}
