#include<cstdio>
#include<cstring>
#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
using namespace std;
const int INF=~0U>>2;
const int MAXN=20010;
const int MAXK=102;
typedef int arr[MAXN];
int n,k,i,j,pos,ans,min0,en0;
arr d,c,s,w,f,st,ed;

struct tree
{
    int min[1<<16],en[1<<16];
    void pdown(int i)
    {
        en[i<<1]+=en[i];min[i<<1]+=en[i];
        en[(i<<1)+1]+=en[i];min[(i<<1)+1]+=en[i];
        en[i]=0;
    }
    void pup(int i)
    {
        min[i]=MIN(min[i<<1],min[(i<<1)+1]);
    }
    void build(int i,int x,int y)
    {
        en[i]=0;
        if(x!=y)
        {
            build(i<<1,x,(x+y)>>1);
            build((i<<1)+1,((x+y)>>1)+1,y);
            pup(i);
        }
        else min[i]=f[x];
    }
    void find(int i,int x,int y,int l,int r,int kind)
    {
        if(x>y)return;
        if(l>y || r<x)return;
        if(x>=l && y<=r)
        {
            switch(kind)
            {
                case 1: //查找最小值 
                    min0=MIN(min0,min[i]);
                    break;
                case 2: //加上一个值 
                    en[i]+=en0;min[i]+=en0;
                    break;
            }
        }
        else
        {
            pdown(i);
            find(i<<1,x,(x+y)>>1,l,r,kind);
            find((i<<1)+1,((x+y)>>1)+1,y,l,r,kind);
            pup(i);
        }
    }
}a;

struct biao
{
    int edge;
    arr e,b,first,last,w;
    void clean()
    {
        edge=0;
        memset(first,-1,sizeof(first));
        memset(b,-1,sizeof(b));
    }
    void add(int x,int y,int z)
    {
        e[edge]=y;w[edge]=z;
        if(first[x]==-1)first[x]=edge;
        else b[last[x]]=edge;
        last[x]=edge++;
    }
}q;

int findl(int x)
{
    int l,r;
    for(l=1,r=n;l<r;)
    {
        if(x<=d[(l+r)>>1])r=(l+r)>>1;
        else l=((l+r)>>1)+1;
    }
    return l;
}
int findr(int x)
{
    int l,r;
    for(l=1,r=n;l<r;)
    {
        if(x>=d[(l+r+1)>>1])l=(l+r+1)>>1;
        else r=((l+r+1)>>1)-1;
    }
    return l;
}
int main()
{
    freopen("base.in","r",stdin);
    freopen("base.out","w",stdout);
    scanf("%d%d",&n,&k);
    rep(i,2,n)scanf("%d",&d[i]);
    rep(i,1,n)scanf("%d",&c[i]);
    rep(i,1,n)scanf("%d",&s[i]);
    rep(i,1,n)scanf("%d",&w[i]);
    n++;d[n]=INF;k++;
    q.clean();
    rep(i,1,n)
    {
        st[i]=findl(d[i]-s[i]);
        ed[i]=findr(d[i]+s[i]);
        q.add(ed[i],st[i]-1,w[i]);
    }
    
    ans=INF;
    f[0]=0;rep(i,1,n)f[i]=INF;
    rep(j,1,k)
    {
        a.build(1,0,n);
        f[0]=0;rep(i,1,n)f[i]=INF;
        rep(i,1,n)
        {
            min0=INF;
            a.find(1,0,n,0,i-1,1);
            f[i]=min0+c[i];
            for(int pos=q.first[i];pos>=0;pos=q.b[pos])
            {
                en0=q.w[pos];
                a.find(1,0,n,0,q.e[pos],2);
            }
        }
        ans=MIN(ans,f[n]);     
    }
    printf("%d\n",ans);
    
    scanf("\n");
    return 0;
}
