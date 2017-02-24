#include<cstdio>
#include<algorithm>
#include<cstring>
#define rep(i,x,y) for(i=x;i<=y;i++)
#define MIN(x,y) ((x)<(y)?(x):(y))

using namespace std;
const int MAXN=10003;
const int MAXM=80001;
const int f1[]={0, 1,-1, 0, 0};
const int f2[]={0, 0, 0, 1,-1};
const int INF=~0U>>2;

int n,m,i,j,k,t,p;
int a[101][101];
typedef int arredge[MAXM];
typedef int arrdot[MAXN];
int S,T,N,edge,ans;
arredge e,b,c;
arrdot first,last,h,vh,cur,pre;

void add(int x,int y,int z)
{
    e[edge]=y;c[edge]=z;
    if(first[x]==-1)first[x]=edge;
    else b[last[x]]=edge;
    last[x]=edge++;
}
void add_(int x,int y,int z)
{
    add(x,y,z);
    add(y,x,0);
}
int sap()
{
    int i,u,k,minh,maxflow,ans=0;
    rep(i,1,N)pre[i]=h[i]=vh[i]=0,cur[i]=first[i];vh[0]=N;pre[S]=S;
    for(u=S;h[S]<N;)
    {
        if(u==T)
        {
            maxflow=INF;
            for(i=S;i!=T;i=e[cur[i]])maxflow=min(maxflow,c[cur[i]]);
            for(i=S;i!=T;i=e[cur[i]])c[cur[i]]-=maxflow,c[cur[i]^1]+=maxflow;
            ans+=maxflow;u=S;
        }
        for(k=cur[u];k>=0;k=b[k])
        if(c[k]&&h[u]==h[e[k]]+1){cur[u]=k;pre[e[k]]=u;u=e[k];break;}
        if(k<0)
        {
            if(--vh[h[u]]==0)break;
            cur[u]=first[u];minh=N;
            for(k=cur[u];k>=0;k=b[k])if(c[k])minh=min(minh,h[e[k]]+1);
            ++vh[h[u]=minh];u=pre[u];
        }
    }
    return ans;
}


bool pd(int x,int y)
{
    if(x<1 || y<1 || x>n || y>m)return 0;
    return 1;
}
int dot(int x,int y)
{
    return (x-1)*m+y;
}
void read(int&x)
{
    char c;
    for(c=getchar();c<=32;c=getchar());
    for(x=0;c>32;c=getchar())x=x*10+c-'0';
}
int main()
{
    read(n);read(m);
    rep(i,1,n)rep(j,1,m)read(a[i][j]);
    
    
    S=n*m+1;
    T=n*m+2;
    N=n*m+2;
    rep(i,1,N)first[i]=-1;
    rep(i,1,n*m*8)b[i]=-1;
    
    rep(i,1,n)
    rep(j,1,m)
    if(a[i][j]==1)add_(S,dot(i,j),INF);
    else
    if(a[i][j]==2)add_(dot(i,j),T,INF);
    
    rep(i,1,n)
    rep(j,1,m)
    rep(t,1,4)
    if(pd(i+f1[t],j+f2[t]))
    if(a[i][j]==0 || a[i+f1[t]][j+f2[t]]==0 || a[i][j]+a[i+f1[t]][j+f2[t]]==3)
    add_(dot(i,j),dot(i+f1[t],j+f2[t]),1);
    
    printf("%d\n",sap());
    return 0;
}
