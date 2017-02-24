#include<cstdio>
#include<cstring>
#include<cmath>
#define rep(i,x,y) for(i=x;i<=y;i++)
using namespace std;
typedef long long int64;

const int MAXN=100001;
int n,i;
int64 t,delta,u,INF;
bool odd;
int a[MAXN],b[MAXN];
int main()
{
    freopen("coins.in","r",stdin);
    freopen("coins.out","w",stdout);
    scanf("%d",&n);
    scanf("%I64d",&t);
    odd=t&1;
    rep(i,0,n-1)scanf("%d",&a[i]);
    rep(i,0,n-1)a[i]--;
    delta=t/2;INF=int64(ceil(double(t)/n))*n;
    for(;t>0;)
    {
        u=int64(1)<<int64(log(t)/log(2));
        t-=u;
        rep(i,0,n-1)b[i]=a[i];
        rep(i,0,n-1)a[i]^=b[(i+u)%n];
    }
    rep(i,0,n-1)
    {
        if(i>0)printf(" ");
        if(odd)printf("0 %d",a[(i-delta+INF)%n]+1);
        else printf("%d 0",a[(i-delta+INF)%n]+1);
    }
    printf("\n");
    scanf("\n");
    return 0;
}
