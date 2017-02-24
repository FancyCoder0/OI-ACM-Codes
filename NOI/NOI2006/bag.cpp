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

typedef long long int64;
typedef long double real;


int t,n,d,i,j,k,l,p,tot,a[1001],b[1001][2];bool nosol;
int c[100001];
struct bignumber
{
    int l,s[200000];
    void mul(int x)
    {
        int i;
        rep(i,1,l)s[i]*=x;l+=5;
        rep(i,1,l)s[i+1]+=s[i]/10000,s[i]%=10000;
        while(l>1&&s[l]==0)l--;
    }
    void print()
    {
        int i,x;
        printf("%d",s[l]);_rep(i,l-1,1)printf("%04d",s[i]);
    }
}A,B;

void add(int x,int d)
{
    //printf("%d %d\n",x,d);
    for(int i=2;i*i<=x;i++)
    while(x%i==0)x/=i,c[i]+=d;
    if(x>1)c[x]+=d;
}
bool zero(bignumber x)
{
    return x.l==1&&x.s[1]==0;
}
bool same(bignumber a,bignumber b)
{
    if(a.l!=b.l)return 0;
    int i;
    rep(i,1,a.l)if(a.s[i]!=b.s[i])return 0;
    return 1;
}
int main()
{
    freopen("bag.in","r",stdin);
    freopen("bag.out","w",stdout);
    scanf("%d%d%d",&t,&n,&d);
    rep(i,1,t)scanf("%d",&a[i]),tot+=a[i];
    rep(i,1,n)scanf("%d%d",&b[i][0],&b[i][1]);

    nosol=1;
    rep(i,1,n)
    {
        add(tot,-1);
        if(a[b[i][1]]>0)nosol=0;
        add(a[b[i][1]],1);
        a[b[i][1]]+=d;
        tot+=d;
    }
    A.l=A.s[1]=1;rep(i,2,100000)if(c[i]>0)rep(j,1,c[i])A.mul(i);
    B.l=B.s[1]=1;rep(i,2,100000)if(c[i]<0)rep(j,1,-c[i])B.mul(i);
    
    if(nosol)printf("0/1\n");
    else A.print(),printf("/"),B.print(),printf("\n");
    
    scanf("\n");
    return 0;
}
