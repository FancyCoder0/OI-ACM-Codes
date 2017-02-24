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
#define mp make_pair
//#define x first
//#define y second
#define MAX(x,y) ((x)>(y)?(x):(y))
//#define MIN(x,y) ((x)<(y)?(x):(y))
#define sqr(x) ((x)*(x))

typedef long long int64;
typedef long double real;

const int MAXN=10010;
int n,m,i,j,k,l,p,c,x,y,z;
int a[MAXN];

struct tree
{
    int fa[MAXN],son[MAXN][2],key[MAXN],maxs[MAXN],R,t;

    bool rev[MAXN];
    void prev(int i){rev[i]=!rev[i];swap(son[i][0],son[i][1]);}
    void pdown(int i)
    {
        if(rev[i])
        {
            rev[i]=0;
            if(son[i][0])prev(son[i][0]);
            if(son[i][1])prev(son[i][1]);
        }
    }
    void updata(int i){maxs[i]=MAX(MAX(maxs[son[i][0]],maxs[son[i][1]]),key[i]);}
    
    void rot(int i,int t)
    {
        int x,y;
        x=son[i][!t];
        pdown(x);//!!
        y=son[x][t];
        son[i][!t]=y;
        son[x][t]=i;
        fa[y]=i;
        if(fa[i])
            if(son[fa[i]][0]==i)son[fa[i]][0]=x;
            else son[fa[i]][1]=x;
        fa[x]=fa[i];
        fa[i]=x;
        updata(i);
    }
    int spl(int x,int f)
    {
        int y,z;
        pdown(x);
        while(!(fa[x]==f||fa[x]==0))
        {
            y=fa[x];
            z=fa[y];
            if(z)pdown(z);pdown(y);
            if(z==f||z==0)
                if(son[y][0]==x)rot(y,1);else rot(y,0);
            else
            if(son[z][0]==y)
                if(son[y][0]==x)rot(z,1),rot(y,1);
                else rot(y,0),rot(z,1);
            else
                if(son[y][0]==x)rot(y,1),rot(z,0);
                else rot(z,0),rot(y,0);
        }
        updata(x);
    }
    void merge(int x,int y)
    {
        spl(x,0);spl(y,0);
        int kind1=(son[x][0]!=0),kind2=(son[y][0]!=0);
        son[x][kind1]=y;fa[y]=x;
        if(kind1==kind2)prev(y);
        updata(x);
    }
    
    int find(int x,int y)
    {
        if(x==y)return key[x];
        R=0;
        spl(x,0);
        spl(y,x);
        if(fa[y]==x)R=x,t=(son[R][0]!=y);
        else
        {
            spl(y,0);spl(x,y);
            if(fa[x]==y)R=y,t=(son[R][0]!=x);
        }
        
        if(R==0)return -1;
        return MAX(MAX(key[R],key[son[R][t]]),maxs[son[son[R][t]][!t]]);
    }
    bool pd(int x,int y)
    {
        spl(x,0);
        int i=son[x][0];if(i)pdown(i);
        while(son[i][1])pdown(i=son[i][1]);
        if(i==y)return 1;
        i=son[x][1];if(i)pdown(i);
        while(son[i][0])pdown(i=son[i][0]);
        if(i==y)return 1;
        return 0;
    }
    void div(int x,int y)
    {
        find(x,y);
        fa[son[R][t]]=0;
        son[R][t]=0;
        updata(R);
    }
    bool can(int x)
    {
        spl(x,0);
        if(son[x][0]==0||son[x][1]==0)return 1;
        else return 0;
    }
    bool same(int x,int y)
    {
        return(find(x,y)!=-1);
    }
}T[10];

int getcolor(int x,int y)
{
    for(int i=0;i<=c;i++)if(T[i].pd(x,y))return i;
    return -1;
}

int main()
{
    freopen("network.in","r",stdin);
    freopen("network.out","w",stdout);
    scanf("%d%d%d%d",&n,&m,&c,&k);c--;
    rep(i,1,n)scanf("%d",&a[i]);
    rep(i,0,c)rep(j,1,n)T[i].key[j]=T[i].maxs[j]=a[j];
    rep(i,1,m)
    scanf("%d%d%d",&x,&y,&z),T[z].merge(x,y);
    int kind,co;
    for(;k;k--)
    {
        scanf("%d",&kind);
        if(kind==0)
        {
            scanf("%d%d",&x,&y);
            rep(i,0,c){T[i].spl(x,0);T[i].key[x]=y;T[i].updata(x);}
        }
        else if(kind==1)
        {
            scanf("%d%d%d",&x,&y,&z);
            co=getcolor(x,y);
            if(co==-1)printf("No such edge.\n");
            else if(co==z)printf("Success.\n");
            else if(!(T[z].can(x)&&T[z].can(y)))printf("Error 1.\n");
            else if(T[z].same(x,y))printf("Error 2.\n");
            else
            {
                T[co].div(x,y);
                T[z].merge(x,y);
                printf("Success.\n");
            }
        }
        else if(kind==2)
        {
            scanf("%d%d%d",&z,&x,&y);
            printf("%d\n",T[z].find(x,y));
        }
    }
    
    scanf("\n");
    return 0;
}
