#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<iostream>
#include<set>
#include<cmath>
using namespace std;
typedef long long int64;
typedef long double real;
#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
const int MAXN=110;
char readc(){char x;for(x=getchar();x<=32;x=getchar());return x;}

int n,m,i,j,e[MAXN*2];
int lowbit(int x){return x&-x;}
int log2(int x){return x==1?0:log2(x/2)+1;}
int sg(int x,int y)
{
    //if(x==0||y==0)return int(log(lowbit(x+y+1))/log(2));
    if(x==0||y==0)return log2(lowbit(x+y+1));
    else return x+y;
}
int main()
{
    int cases;
    //printf("%d\n",int(log(100)/log(2)));
    scanf("%d",&cases);
    for(int number=1;number<=cases;number++)
    {
        scanf("%d%d",&n,&m);
        memset(e,0,sizeof(e));
        rep(i,0,n-1)
        rep(j,0,m-1)
        {
            char c=readc();
            if(c=='T')e[sg(i,j)]^=1;
        }
        bool ok=1;
        rep(i,0,n+m)if(e[i]){ok=0;break;}
        if(ok)printf("=_=\n");else printf("-_-\n");
        
    }
    scanf("\n");
}
