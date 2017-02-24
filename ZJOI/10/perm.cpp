#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<iostream>
using namespace std;
typedef long long int64;
typedef long double real;
#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
const int MAXN=2000010;
int n,i,j;
int64 p;
int64 c[MAXN],g[MAXN],f[MAXN];
int64 pow(int64 x,int64 y)
{
    //if(y<0)printf("%lld %lld NO!\n",x,y);
    if(y==0)return 1;
    int64 ans=pow(x,y/2);
    ans=ans*ans%p;
    if(y&1)ans=ans*x%p;
    return ans;
}

int64 work(int i)
{
    if(f[i]!=-1)return f[i];
    return f[i]=work(g[i])*work(i-1-g[i])%p*c[i-1]%p*pow(c[g[i]],p-2)%p*pow(c[i-1-g[i]],p-2)%p;
}
int main()
{
    freopen("perm.in","r",stdin);
    freopen("perm.out","w",stdout);
    scanf("%d",&n);
    cin>>p;
    c[0]=1;rep(i,1,n)c[i]=c[i-1]*i%p;
    rep(i,1,19)
    {
        g[1<<i]=1<<(i-1);
        rep(j,1,(1<<(i-1))-1)
        g[(1<<i)+j]=(1<<(i-1))+j;
    }
    rep(i,2,n)if(g[i]==0)g[i]=g[i-1];
    
    rep(i,1,n)f[i]=-1;
    f[1]=f[2]=1;
    cout<<work(n)<<endl;
    
    scanf("\n");
    return 0;
} 
