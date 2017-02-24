#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,x,y) for(i=x;i<=y;i++)
using namespace std;
typedef long long int64;
const int MAXN=200010;
const int P=999983;
int n,i,j,k,l,p,maxdis;
int a[MAXN][3];
int hashg[P];
int64 hash[P][8];
int hashnum[P][8];
int edge,e[MAXN*6],b[MAXN*6],first[MAXN],last[MAXN],q[MAXN],dis[MAXN];
void clear(){edge=0;memset(first,-1,sizeof(first));memset(b,-1,sizeof(b));}
void add(int x,int y){/*if(y==-1)return;printf("%d %d\n",x,y);*/e[edge]=y;if(first[x]==-1)first[x]=edge;else b[last[x]]=edge;last[x]=edge++;}

int find_hash(int64 x,int num)
{
    int i,ans=0;
    rep(i,0,hashg[x%P]-1)
    if(hash[x%P][i]==x&&hashnum[x%P][i]!=num)
    return hashnum[x%P][i];
    return -1;
}
void ins_hash(int64 x,int num)
{
    int i,ans=0;
    rep(i,0,hashg[x%P]-1)
    if(hash[x%P][i]==x&&hashnum[x%P][i]==num)return;
    hash[x%P][hashg[x%P]]=x;
    hashnum[x%P][hashg[x%P]]=num;
    hashg[x%P]++;
}

int BFS(int start)
{
    int i,j,k,max0;
    maxdis=0;
    memset(dis,127,sizeof(dis));
    i=j=1;q[1]=start;dis[start]=1;
    for(;i<=j;i++)
    for(k=first[q[i]];k>=0;k=b[k])
    if(dis[q[i]]+1<dis[e[k]])
    {
        dis[e[k]]=dis[q[i]]+1;
        q[++j]=e[k];
        if(dis[e[k]]>maxdis)maxdis=dis[e[k]],max0=e[k];
    }
    return max0;
}
int main()
{
    freopen("journey.in","r",stdin);
    freopen("journey.out","w",stdout);
    scanf("%d",&n);
    rep(i,1,n-2)scanf("%d%d%d",&a[i][0],&a[i][1],&a[i][2]);
    rep(i,1,n-2)
    ins_hash((int64)a[i][0]*n+a[i][1],i),
    ins_hash((int64)a[i][0]*n+a[i][2],i),
    ins_hash((int64)a[i][1]*n+a[i][2],i);
    
    clear();
    rep(i,1,n-2)
    add(i,find_hash((int64)a[i][0]*n+a[i][1],i)),
    add(i,find_hash((int64)a[i][0]*n+a[i][2],i)),
    add(i,find_hash((int64)a[i][1]*n+a[i][2],i)),
    add(i,find_hash((int64)a[i][1]*n+a[i][0],i)),
    add(i,find_hash((int64)a[i][2]*n+a[i][0],i)),
    add(i,find_hash((int64)a[i][2]*n+a[i][1],i));
    
    BFS(BFS(1));
    printf("%d\n",maxdis);
    
    scanf("\n");
    return 0;
}
