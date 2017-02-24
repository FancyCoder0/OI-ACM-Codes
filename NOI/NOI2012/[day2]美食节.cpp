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
using namespace std; 
  
#define rep(i,x,y) for(i=x;i<=y;i++) 
#define _rep(i,x,y) for(i=x;i>=y;i--) 
#define CL(S,x) memset(S,x,sizeof(S)) 
#define CP(S1,S2) memcpy(S1,S2,sizeof(S2)) 
#define mp make_pair 
//#define x first 
//#define y second 
//#define MAX(x,y) ((x)>(y)?(x):(y)) 
#define MIN(x,y) ((x)<(y)?(x):(y)) 
#define sqr(x) ((x)*(x)) 
  
typedef long long int64; 
typedef long double real; 
  
  
const int MAXN=80051; 
const int MAXM=3280041*2; 
const int INF=1000000000; 
int m,n,i,j,k,l,p,S,T,N,t,ans;int a[41][101],p0[41]; 
int edge,first[MAXN],last[MAXN],e[MAXM],b[MAXM],c[MAXM],w[MAXM],home[MAXN],level[MAXN]; 
int dis[MAXN],v[MAXN],q[MAXM],fa[MAXM],faw[MAXM]; 
void clear(){CL(first,-1);CL(b,-1);} 
//void _add(int x,int y,int z,int q){e[edge]=y;c[edge]=z;w[edge]=q;b[edge]=first[x];first[x]=edge++;} 
void _add(int x,int y,int z,int q){e[edge]=y;c[edge]=z;w[edge]=q;if(first[x]==-1)first[x]=edge;else b[last[x]]=edge;last[x]=edge++;} 
void add(int x,int y,int z,int q){_add(x,y,z,q);_add(y,x,0,-q);} 
  
bool SPFA()  
{  
    int i,j,u,k,iii,I;  
    rep(i,1,N)dis[i]=INF,v[i]=-1;  
    i=0;j=0;q[0]=S;v[S]=0;dis[S]=0;  
    while(i<=j)  
    {  
        u=q[i];  
        for(k=first[u];k>=0;k=b[k])  
        if(c[k]&&dis[u]+w[k]<dis[e[k]])  
        if(dis[u]+w[k]<dis[T]) 
        {  
            dis[e[k]]=dis[u]+w[k];  
            if(v[e[k]]==-1)  
            {  
                q[++j]=e[k];  
                v[q[j]]=j;  
                fa[j]=i;  
                faw[j]=k;  
            }  
            else
            {  
                fa[v[e[k]]]=i;  
                faw[v[e[k]]]=k;  
            }  
        }  
        v[u]=-1;  
        if(u==T)iii=i;  
        i++;  
    }  
    if(dis[T]==INF)return 0;  
        
    for(i=iii;i!=0;i=fa[i]) 
    { 
        c[faw[i]]-=1,c[faw[i]^1]+=1;  
        k=home[q[i]]; 
        if(k&&level[k]<p) 
        { 
            level[k]++; 
            rep(I,1,n)add(I,(k-1)*p+level[k]+n,1,level[k]*a[I][k]); 
        } 
    } 
    ans+=dis[T];  
    return 1;  
}  
    
  
int main() 
{ 
    scanf("%d%d",&n,&m); 
    rep(i,1,n)scanf("%d",&p0[i]),p+=p0[i]; 
    rep(i,1,n)rep(j,1,m)scanf("%d",&a[i][j]); 
      
    S=m*p+n+1; 
    N=T=m*p+n+2; 
      
    clear(); 
    rep(i,1,n)add(S,i,p0[i],0); 
    rep(j,1,m)rep(k,1,p)home[(j-1)*p+k+n]=j,add((j-1)*p+k+n,T,1,0); 
    rep(i,1,n)rep(j,1,m)level[j]=1,add(i,(j-1)*p+1+n,1,a[i][j]); 
    
    while(SPFA()); 
    printf("%d\n",ans); 
    return 0; 
} 
