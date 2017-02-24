#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define rep(i,x,y) for(i=x;i<=y;i++)
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
using namespace std;
typedef long long int64;
const int MAXN=1010;

int n,m,i,j,k,p,ll,rr;
int a[MAXN];
int f[MAXN][MAXN];
int l[MAXN][MAXN],r[MAXN][MAXN];
void get(int i,int j)
{
    if(l[i][j]!=-1)return;
    get(i+1,j);get(i,j-1);
    ll=l[i][j-1];
    rr=r[i+1][j];
    if(ll<rr)
    {
        if(a[j]==rr)l[i][j]=0;
        else
        if(a[j]>rr || a[j]<ll)l[i][j]=a[j];
        else
        l[i][j]=a[j]+1;
        
        if(a[i]==ll)r[i][j]=0;
        else
        if(a[i]<ll || a[i]>rr)r[i][j]=a[i];
        else
        r[i][j]=a[i]-1;
    }
    else
    {
        if(a[j]==rr)l[i][j]=0;
        else
        if(a[j]>ll || a[j]<rr)l[i][j]=a[j];
        else l[i][j]=a[j]-1;
        
        if(a[i]==ll)r[i][j]=0;
        else
        if(a[i]<rr || a[i]>ll)r[i][j]=a[i];
        else r[i][j]=a[i]+1;
    }
}

int main()
{
    int cases;
    scanf("%d",&cases);
    int number;
    rep(number,1,cases)
    {
        scanf("%d",&n);
        rep(i,1,n)scanf("%d",&a[i]);
        rep(i,1,n)
        rep(j,1,n)
        if(i==j)l[i][j]=r[i][j]=0;
        else l[i][j]=r[i][j]=-1;
        get(1,n);
        if(r[1][n]==a[n])printf("0\n");
        else printf("1\n");
    }
    scanf("\n");
    return 0;
}
