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
//#include<iostream>
//#include<cmath>
using namespace std;

#define rep(i,x,y) for(i=x;i<=y;i++)
#define _rep(i,x,y) for(i=x;i>=y;i--)
#define CL(S,x) memset(S,x,sizeof(S))
#define mp make_pair
//#define x first
//#define y second
//#define MAX(x,y) ((x)>(y)?(x):(y))
//#define MIN(x,y) ((x)<(y)?(x):(y))
//#define sqr(x) ((x)*(x))

typedef long long int64;
typedef long double real;

const int MAXN=66000;
const int MAXM=2000010;

int n,i,j,k,l,p,x;
int e[MAXM],b[MAXM],first[MAXN],last[MAXN],edge,q[MAXN],d[MAXN];
int size[MAXN];
int fa[MAXN][17],dep[MAXN];
vector<int> list[MAXN];
void add(int x,int y){d[y]++;e[edge]=y;if(first[x]==-1)first[x]=edge;else b[last[x]]=edge;last[x]=edge++;}
void tp()
{
    i=1;j=1;q[1]=0;
    for(;i<=j;i++)
    for(int k=first[q[i]];k>=0;k=b[k])
    {
        d[e[k]]--;
        if(d[e[k]]==0)q[++j]=e[k];
    }
}
int log2(int x){return x==0?-1:log2(x/2)+1;}
void go_up(int &x,int y)
{
    for(int t=log2(y);t>=0;t--)
    if(y>>t & 1)x=fa[x][t];
}
int LCA(int x,int y)
{
    if(dep[x]>dep[y])go_up(x,dep[x]-dep[y]);else go_up(y,dep[y]-dep[x]);
    if(x==y)return x;
    for(int t=log2(dep[x]);t>=0;t--)
    if(fa[x][t]!=fa[y][t])x=fa[x][t],y=fa[y][t];
    return fa[x][0];
}
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d",&n);
    CL(first,-1);CL(b,-1);
    rep(i,1,n)for(scanf("%d",&x);x!=0;scanf("%d",&x))add(x,i),list[i].push_back(x);
    rep(i,1,n)if(d[i]==0)add(0,i),list[i].push_back(0);
    tp();
    vector<int>::iterator pos;
    int u,L,t;
    rep(i,2,n+1)
    {
        u=q[i];L=-1;
        for(pos=list[u].begin();pos!=list[u].end();pos++)
        {
            if(L==-1)L=*pos;else L=LCA(L,*pos);
        }
        dep[u]=dep[L]+1;fa[u][0]=L;
        for(t=1;(1<<t)<=dep[u];t++)fa[u][t]=fa[fa[u][t-1]][t-1];
    }
    _rep(i,n+1,2)
    {
        size[q[i]]++;
        size[fa[q[i]][0]]+=size[q[i]];
    }
    rep(i,1,n)printf("%d\n",size[i]-1);
    scanf("\n");
    return 0;
}
