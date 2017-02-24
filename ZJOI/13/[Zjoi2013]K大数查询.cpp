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

const int MAXN=50010;
const int MAXD=20000010;
int n,m,tot,i,j,k,kind,x,y,z,cnt;
int ask[MAXN][4],a[MAXN];
int root[MAXD],L[MAXD],R[MAXD],sum[MAXD],add[MAXD];
inline int find(int i,int x,int y,int l,int r,int mark,int s)
{
    if(y<l||x>r)return i;
    if(!i)i=++tot;
    
    if(s)sum[i]+=min(y,r)-max(x,l)+1;
    if(x>=l&&y<=r)
    {
        if(s)add[i]++;
        else cnt+=sum[i]+mark*(y-x+1);
    }
    else
    {
        L[i]=find(L[i],x,(x+y)/2,l,r,mark+add[i],s);
        R[i]=find(R[i],(x+y)/2+1,y,l,r,mark+add[i],s);
    }
    return i;
}
inline void treeins(int l,int r,int c)
{
    int i=1,x=1,y=a[0];
    while(1)
    {
        root[i]=find(root[i],1,n,l,r,0,1);
        if(x==y)break;
        if(c<=(x+y)/2)i=i*2,y=(x+y)/2;
        else i=i*2+1,x=(x+y)/2+1;
    }
}
inline int treeask(int l,int r,int k)
{
    int i=1,x=1,y=a[0];
    while(1)
    {
        if(x==y)return x;
        cnt=0;root[i*2+1]=find(root[i*2+1],1,n,l,r,0,0);
        if(k<=cnt)i=i*2+1,x=(x+y)/2+1;
        else k-=cnt,i=i*2,y=(x+y)/2;
    }
}
int main()
{
     scanf("%d%d",&n,&m);
    rep(i,1,m)scanf("%d%d%d%d",&ask[i][0],&ask[i][1],&ask[i][2],&ask[i][3]);
    rep(i,1,m)if(ask[i][0]==1)a[++a[0]]=ask[i][3];
    sort(a+1,a+1+a[0]);
    j=1;rep(i,2,a[0])if(a[i]!=a[i-1])a[++j]=a[i];a[0]=j;
    
    rep(i,1,m)
    {
        kind=ask[i][0];x=ask[i][1];y=ask[i][2];z=ask[i][3];
        if(kind==1)
        {
            z=lower_bound(a+1,a+1+a[0],z)-a;
            treeins(x,y,z);
        }
        else
        {
            printf("%d\n",a[treeask(x,y,z)]);
        } 
    }
    
    
    scanf("\n");
    return 0;
}
