#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<iostream>
#include<set>
#include<cmath>
using namespace std;
typedef long long int64;
typedef long double real;
#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
const int MAXN=31;
const int MAXM=31;
const real INF=1e9;
const real zero=1e-6;
int cases,number,i,n,m,N,S,T;
int p[MAXN],r[MAXN],d[MAXN],s[MAXM],h[2000],vh[2000],first[2000],last[2000];
int edge,e[200000],b[200000];real c[200000];
real LEFT,RIGHT;
vector<real> ti;

void add_(int x,int y,real z)
{
    e[edge]=y;c[edge]=z;
    if(first[x]==-1)first[x]=edge;
    else b[last[x]]=edge;
    last[x]=edge++;
}
void add(int x,int y,real z)
{
    add_(x,y,z);
    add_(y,x,0);
}
real ISAP(int i,real flow)
{
    if(i==T)return flow;
    int k,minh=N;
    real r=flow,d;
    for(k=first[i];k>=0;k=b[k])
    if(c[k]>zero)
    {
        if(h[i]==h[e[k]]+1)
        {
            d=ISAP(e[k],MIN(c[k],r));
            c[k]-=d;c[k^1]+=d;r-=d;
            if(h[S]>=N)return flow-r;
            if(r<zero)break;
        }
        minh=MIN(minh,h[e[k]]+1);
    }
    if(abs(flow-r)<zero)
    {
        if(--vh[h[i]]==0)h[S]=N;
        vh[h[i]=minh]++;
    }
    return flow-r;
}
real work()
{
    memset(h,0,sizeof(h));
    memset(vh,0,sizeof(vh));
    vh[0]=N;
    real ans=0;
    while(h[S]<N)
    ans+=ISAP(S,INF);
    //cout<<ans<<endl;
    return ans;
}

int getnum(int i,int j)
{
    return (i-1)*m+j;
}
bool ok(real time0)
{
    real need=0;
    edge=0;memset(first,-1,sizeof(first));memset(b,-1,sizeof(b));
    int i,j,k;
    S=2*n*m+n+1;
    T=2*n*m+n+2;
    N=T;
    rep(i,1,n)need+=(real)p[i];
    rep(i,1,n)add(i,T,(real)p[i]);
    
    vector<real> ti;
    rep(i,1,n)ti.push_back(r[i]),ti.push_back(d[i]+time0);
    sort(ti.begin(),ti.end());
    rep(i,1,ti.size()-1)
    {
        //printf("%d\n",ti.size());
        real dt=ti[i]-ti[i-1];
        rep(j,1,m)add(S,getnum(i,j)+n,dt*s[j]*j);
        rep(j,1,m)
        rep(k,1,n)
        if((r[k]-zero<ti[i-1])&&(ti[i]<d[k]+time0+zero))
        add(getnum(i,j)+n,k,dt*s[j]);
    }
    
    //cout<<"ans="<<work()<<endl;
    if(abs(need-work())<=zero)return 1;
    return 0;
}

bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    freopen("cheese.in","r",stdin);
    freopen("cheese.out","w",stdout);
    scanf("%d",&cases);
    rep(number,1,cases)
    {
        scanf("%d%d",&n,&m);
        rep(i,1,n)scanf("%d%d%d",&p[i],&r[i],&d[i]);
        rep(i,1,m)scanf("%d",&s[i]);
        s[m+1]=0;
        sort(s+1,s+1+m,cmp);
        rep(i,1,m)s[i]=s[i]-s[i+1];
        
        LEFT=0;RIGHT=INF;
        while(RIGHT-LEFT>zero)
        {
            //cout<<LEFT<<' '<<RIGHT<<endl;
            if(ok((LEFT+RIGHT)/2))RIGHT=(LEFT+RIGHT)/2;
            else LEFT=(LEFT+RIGHT)/2;
        } 
        cout<<fixed<<setprecision(6)<<(LEFT+RIGHT)/2<<endl;
    }
    
    scanf("\n");
    return 0;
}
