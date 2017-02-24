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

const int MAXN=610;
const int MAXM=8010;
const real inf=1e18;
const real eps=1e-8;
struct node{real x,y;};
struct line{node a,b;};
inline bool operator==(node a,node b){return abs(a.x-b.x)<eps&&abs(a.y-b.y)<eps;}
inline node operator+(node a,node b){return (node){a.x+b.x,a.y+b.y};}
inline node operator-(node a,node b){return (node){a.x-b.x,a.y-b.y};}
inline real operator*(node a,node b){return a.x*b.y-a.y*b.x;}
inline real xj(node a,node b,node c){return (b-a)*(c-a);}

inline bool jiao(line a,line b)
{
    return ((xj(a.a,a.b,b.a)>0)^(xj(a.a,a.b,b.b)>0))&&
           ((xj(b.a,b.b,a.a)>0)^(xj(b.a,b.b,a.b)>0));
}

int n,m,i,j,k,l,p,x,y,z,g,tot,N,num[MAXN];real sum[MAXN];
node a[MAXN],S[MAXM],X,Y,de,zhong;
int find(node a){int i;rep(i,1,tot)if(a==S[i])return i;S[++tot]=a;return tot;}
int e[MAXM][2],cf[MAXM],next[MAXM],belong[MAXM];
struct dot{int edgenum;real alp;};
bool cmp(dot a,dot b){return a.alp<b.alp;}
vector<dot> line0[MAXM];
vector<dot>::iterator pos,pos2;

vector<line> Ed[MAXN];
vector<line>::iterator it;

bool r[MAXN][MAXN];
pair<real,int> list[MAXN];

inline bool inside(node x,int k)
{
    int cnt=0;
    for(it=Ed[k].begin();it!=Ed[k].end();it++)
    if(jiao(*it,(line){x,(node){1e8+5,2e8+7}}))cnt++;
    return cnt&1;
}

inline int shuyu(node x)
{
   g=0;int ans=0;real mins=inf;
   rep(j,1,n)if(inside(x,j))
   if(sum[j]<mins)mins=sum[j],ans=j;
   return ans;
}

int main()
{
    freopen("risk.in","r",stdin);
    freopen("risk.out","w",stdout);
    scanf("%d%d",&n,&m);
    rep(i,1,n)scanf("%lf%lf",&a[i].x,&a[i].y),a[i]=a[i];
    rep(i,1,m)
    {
        scanf("%lf%lf",&X.x,&X.y);
        scanf("%lf%lf",&Y.x,&Y.y);
        x=find(X);y=find(Y);
        e[i*2-1][0]=x;e[i*2-1][1]=y;cf[i*2-1]=i*2;
        e[i*2][0]=y;e[i*2][1]=x;cf[i*2]=i*2-1;
        
        line0[x].push_back((dot){i*2-1,-atan2(Y.y-X.y,Y.x-X.x)});
        line0[y].push_back((dot){i*2,-atan2(X.y-Y.y,X.x-Y.x)});
    }
    
    rep(i,1,tot)sort(line0[i].begin(),line0[i].end(),cmp);
    rep(i,1,tot)
    {
        for(pos=line0[i].begin();pos!=line0[i].end();pos++)
        {
            if(pos+1==line0[i].end())pos2=line0[i].begin();else pos2=pos+1;
            next[(*pos).edgenum]=(*pos2).edgenum;
        }
    }
    
    rep(i,1,2*m)
    if(!belong[i])
    {
        ++N;
        for(sum[N]=0,p=i;;)
        {
            belong[p]=N;
            sum[N]+=S[e[p][0]]*S[e[p][1]];
            p=next[cf[p]];
            if(p==i)break;
        }
        if(sum[N]<0){N--;for(p=i;;){belong[p]=0;p=next[cf[p]];if(p==i)break;}}
    }
    
    
    rep(i,1,2*m)if(belong[i])Ed[belong[i]].push_back((line){S[e[i][0]],S[e[i][1]]});
    rep(i,1,2*m)
    if(belong[cf[i]]==0)
    {
        x=belong[i];
        de=(node){1e-8,1e-8};
        zhong=(node){(S[e[i][0]].x+S[e[i][1]].x)/2,(S[e[i][0]].y+S[e[i][1]].y)/2};
        y=shuyu(zhong+de);if(x==y)y=shuyu(zhong-de);
        belong[cf[i]]=y;
    }
    
    rep(i,1,2*m)r[belong[i]][belong[cf[i]]]=1;
    rep(i,1,n)num[i]=shuyu(a[i]);
    rep(i,1,n)
    {
        tot=0;rep(j,1,n)if(r[num[i]][num[j]])tot++;
        printf("%d",tot);
        rep(j,1,n)if(r[num[i]][num[j]])printf(" %d",j);
        printf("\n");
    }
    
    scanf("\n");
    return 0;
}
