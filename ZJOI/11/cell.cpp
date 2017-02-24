#include<cstdio>
#include<cstring>
#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
using namespace std;
typedef long long int64;
const int MAXN=1010;
const int64 P=int64(1e9+7);
int s[MAXN];
char c;
struct mat
{
    int64 a[2][2];
}g[MAXN][10],f[MAXN],yuan,SUM,t;
int n,m,i,j,k,l;

mat operator *(const mat &a,const mat &b)
{
    mat c;
    int i,j,k;
    rep(i,0,1)
    rep(j,0,1)
    {
        c.a[i][j]=0;
        rep(k,0,1)
        c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%P)%P;
    }
    return c;
}
mat operator +(const mat &a,const mat &b)
{
    mat c;
    int i,j;
    rep(i,0,1)
    rep(j,0,1)
    c.a[i][j]=(a.a[i][j]+b.a[i][j])%P;
    return c;
}

int main()
{
    scanf("%d\n",&n);
    rep(i,1,n)
    {
        scanf("%c",&c);
        s[i]=c-'0';
        //s[i]=i%9+1;
        if(i<n)scanf("\n");
    }
    
    yuan.a[1][0]=yuan.a[0][1]=yuan.a[1][1]=1;
    g[0][1]=yuan;rep(i,2,9)g[0][i]=g[0][i-1]*yuan;
    rep(i,1,n)
    {
        g[i][1]=g[i-1][1];rep(j,2,10)g[i][1]=g[i][1]*g[i-1][1];
        rep(j,2,9)
        g[i][j]=g[i][j-1]*g[i][1];
    }
    
    f[0]=yuan;
    rep(i,1,n)
    {
        rep_(j,i-1,0)
        {
            if(j==i-1)SUM=g[i-j-1][s[j+1]];
            else SUM=SUM*g[i-j-1][s[j+1]];
            f[i]=f[i]+SUM*f[j];
        }
    }
    
    t.a[0][0]=-1;
    t.a[1][0]=1;
    t=f[n]*t;
    //t=t*f[n];
    printf("%lld\n",(t.a[0][0]%P+P)%P);
    
    
    scanf("\n");
    return 0;
}
