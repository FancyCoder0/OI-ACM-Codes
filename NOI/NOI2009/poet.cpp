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

const int MAXN=100010;
const real inf=1e18;
int cases,n,L,P,i,j,k,len,top,start,thel,ther,mid;char a[MAXN][32];
int st[MAXN][2],s[MAXN],l[MAXN],r[MAXN],id[MAXN],jc[MAXN];
real f[MAXN];int64 g[MAXN];
real pow(int x,int y){real ans=1;for(;y;y--)ans*=x;return ans;}
int64 tpow(int x,int y){int64 ans=1;for(;y;y--)ans*=x;return ans;}
real get(int n,int i){return f[i]+pow(abs(s[n]-s[i]-1-L),P);}
int64 tget(int n,int i){return g[i]+tpow(abs(s[n]-s[i]-1-L),P);}
bool pd(int n,int i,int j){return get(n,i)<get(n,j);}

int main()
{
    //freopen("poet.in","r",stdin);
    //freopen("poet.out","w",stdout);
    for(scanf("%d",&cases);cases;cases--)
    {
        scanf("%d%d%d",&n,&L,&P);
        rep(i,1,n)scanf("%s",a[i]),s[i]=strlen(a[i])+1;
        rep(i,1,n)s[i]+=s[i-1];
        top=1;id[1]=0;l[1]=1;r[1]=n;start=1;
        rep(i,1,n)
        {
            if(i>r[start])start++;jc[i]=id[start];f[i]=get(i,jc[i]);
            for(;l[top]>i&&pd(l[top],i,id[top]);top--)r[top-1]=r[top];
            
            thel=max(l[top],i+1);ther=r[top];
            for(;thel<ther;)
            {
                mid=(thel+ther)/2;
                if(pd(mid,i,id[top]))ther=mid;else thel=mid+1;
            }
            if(pd(thel,i,id[top]))
            r[top]=thel-1,top++,l[top]=thel,r[top]=n,id[top]=i;
        }
        if(f[n]>inf)printf("Too hard to arrange\n");
        else
        {
            for(len=0,i=n;i;i=jc[i])len++,st[len][0]=jc[i]+1,st[len][1]=i;
            _rep(i,len,1)g[st[i][1]]=tget(st[i][1],st[i][0]-1);
            printf("%I64d\n",g[n]);
            /*
            _rep(i,len,1)
            {
                rep(j,st[i][0],st[i][1])
                {
                    if(j>st[i][0])printf(" ");
                    printf("%s",a[j]);
                }
                printf("\n");
            }
            */
        }
        printf("--------------------\n");
    }
    
    scanf("\n");
    return 0;
}
