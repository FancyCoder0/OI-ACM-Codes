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

const int MAXN=1100;
const int MAXM=100010;
const int inf=2000000000;
int n,m,i,j,k,l,p,x,y,z,ans;
int C[1111];

int edge,S,T,N,fir[MAXN],last[MAXN],e[MAXM],b[MAXM],c[MAXM],w[MAXM];
int cur[MAXN],vh[MAXN],h[MAXN],dis[MAXN],de[MAXN];int q[MAXM*10];
bool v[MAXN],o[MAXN];

void clear(){edge=0;CL(b,-1);CL(fir,-1);}
void add2(int x,int y,int z,int q)
{
    e[edge]=y;c[edge]=z;w[edge]=q;
    if(fir[x]==-1)fir[x]=edge;else b[last[x]]=edge;
    last[x]=edge++;
}
void add(int x,int y,int z,int q){
    //printf("%d %d %d %d\n",x,y,z,q);
    add2(x,y,z,q);add2(y,x,0,-q);}
void spfa()
{
    int i,j,k,u;
    CL(dis,127);CL(v,0);
    q[1]=S;dis[S]=0;v[S]=1;
    for(i=j=1;u=q[i],i<=j;v[u]=0,i++)
    for(k=fir[u];k>=0;k=b[k])if(c[k])
    if(dis[u]+w[k]<dis[e[k]])
    {
        dis[e[k]]=dis[u]+w[k];
        if(!v[e[k]])
        {
            v[e[k]]=1;
            q[++j]=e[k];
        }
    }
}
int zkw(int i,int flow)
{
    int d,l,r=flow;
    if(i==T){ans+=dis[i]*flow;return flow;}
    v[i]=o[i]=1;
    for(int&k=cur[i];k>=0;k=b[k])
    if(c[k])
    {
        l=dis[i]+w[k]-dis[e[k]];
        de[e[k]]=min(de[e[k]],l);
        if(l==0&&!o[e[k]])
        {
            d=zkw(e[k],min(c[k],r));
            c[k]-=d;c[k^1]+=d;r-=d;
            if(r==0)break;
        }
    }
    o[i]=0;
    return flow-r;
}
void solve()
{
    spfa();
    CL(v,0);CL(o,0);
    int i,tmp;ans=0;
    while(1)
    {
        rep(i,1,N)de[i]=inf,v[i]=0,cur[i]=fir[i];
        zkw(S,inf);
        tmp=inf;rep(i,1,N)if(!v[i])tmp=min(tmp,de[i]);
        if(tmp==inf)break;
        rep(i,1,N)if(!v[i])dis[i]+=tmp;
    }
    cout<<-ans<<endl;
}
int main()
{
    //freopen("defend.in","r",stdin);
    //freopen("defend.out","w",stdout);
    scanf("%d%d",&n,&m);
    rep(i,1,n)scanf("%d",&C[i]);
    
    clear();S=n+2;T=n+3;N=n+3;
    rep(i,1,m)
    {
        scanf("%d%d%d",&x,&y,&z);
        add(x,y+1,inf,-z);
    }
    
    rep(i,1,n+1)
    {
        int c=C[i]-C[i-1];
        if(c>=0)add(S,i,c,0);
        else add(i,T,-c,0);
        if(i>1)add(i-1,i,inf,0);
    }
    solve();
    scanf("\n");
    return 0;
}
