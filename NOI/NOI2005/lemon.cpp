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
typedef double real;

const int MAXN=510;
const real eps=1e-6;
int n,i,j,k,p;real t,L0,R0,h,x[MAXN],r[MAXN],alp;bool can[MAXN];
real gx1[MAXN],gx2[MAXN],gy1[MAXN],gy2[MAXN];

real get(real x0)
{
    int i;real ma=0;
    rep(i,1,n)
    {
        if(abs(x[i]-x0)<=r[i])ma=max(ma,sqrt(sqr(r[i])-sqr(x[i]-x0)));
        if(can[i]&&x0>=gx1[i]&&x0<=gx2[i])
        ma=max(ma,(gy2[i]-gy1[i])/(gx2[i]-gx1[i])*(x0-gx1[i])+gy1[i]);
    }
    return ma;
}
real ans(real d,real lx,real mx,real rx){return d/6*(lx+rx+4*mx);}
real sim(real l,real m,real r,real lx,real mx,real rx,real sum)
{
    real m1=(l+m)/2,m1x=get(m1),m1s=ans(m-l,lx,m1x,mx),
         m2=(m+r)/2,m2x=get(m2),m2s=ans(r-m,mx,m2x,rx);
    if(abs(m1s+m2s-sum)<eps)return m1s+m2s;
    return sim(l,m1,m,lx,m1x,mx,m1s)+sim(m,m2,r,mx,m2x,rx,m2s);
}
int main()
{
    freopen("lemon.in","r",stdin);
    freopen("lemon.out","w",stdout);
    scanf("%d%lf",&n,&alp);alp=1/tan(alp);
    rep(i,1,n+1)scanf("%lf",&x[i]),h+=x[i],x[i]=h*alp;
    L0=R0=x[n+1];rep(i,1,n)scanf("%lf",&r[i]),L0=min(L0,x[i]-r[i]),R0=max(R0,x[i]+r[i]);
    
    rep(i,1,n)if(sqr(x[i]-x[i+1])-sqr(r[i]-r[i+1])>0)
    {
        can[i]=1;
        t=(r[i+1]-r[i])/(x[i+1]-x[i]);
        gx1[i]=x[i]-t*r[i];
        gx2[i]=x[i+1]-t*r[i+1];
        gy1[i]=sqrt(sqr(r[i])-sqr(x[i]-gx1[i]));
        gy2[i]=sqrt(sqr(r[i+1])-sqr(x[i+1]-gx2[i]));
    }
    
    real L0x=get(L0),R0x=get(R0),M0x=get((L0+R0)/2);
    printf("%.2lf\n",2*sim(L0,(L0+R0)/2,R0,L0x,M0x,R0x,ans(R0-L0,L0x,M0x,R0x)));
    scanf("\n");
    return 0;
}
