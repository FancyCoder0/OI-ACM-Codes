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
#define upmin(x,y) x=min(x,y)
#define upmax(x,y) x=max(x,y)

typedef long long int64;
typedef long double real;
void read(int&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
char getc(){char c;for(c=getchar();c<=32;c=getchar());return c;}

const int N=155;
const int M=510;
int n,m,i,j,k,l,r,p;
int a[N][M],up[N][M],le[N][M];

int f3[M][3],f2[M][3];
int b3[M],b2[M];
int f[4][N][N],f0[4][N][N],g[3][N][N],g2[3][N][N];int ans;

int main()
{
    freopen("penman.in","r",stdin);
    freopen("penman.out","w",stdout);
    scanf("%d%d",&n,&m);
    rep(i,1,n)rep(j,1,m)scanf("%d",&a[i][j]);
    rep(i,1,n)rep(j,1,m)up[i][j]=up[i-1][j]+a[i][j];
    rep(i,1,n)rep(j,1,m)le[i][j]=le[i][j-1]+a[i][j];
    
    CL(b3,200);
    rep(l,1,n)
    rep(r,l+2,n)
    {
        CL(f3,200);
        _rep(j,m,1)
        {
            f3[j][0]=a[l][j]+a[r][j]+max(0,f3[j+1][0]);
            f3[j][1]=(up[r][j]-up[l-1][j])+max(f3[j+1][1],f3[j+1][0]);
            f3[j][2]=a[l][j]+a[r][j]+max(f3[j+1][2],f3[j+1][1]);
            
            b3[j]=max(b3[j],f3[j][2]);
        }
    }
    _rep(j,m,1)b3[j]=max(b3[j],b3[j+1]);
    //rep(i,1,m)printf("%d ",b3[i]);printf("\n");
    
    CL(b2,200);
    rep(l,1,m)
    rep(r,l+2,m)
    {
        CL(f2,200);
        rep(i,1,n)
        {
            f2[i][0]=(le[i][r]-le[i][l-1]);
            f2[i][1]=a[i][r]+a[i][l]+max(f2[i-1][0],f2[i-1][1]);
            f2[i][2]=(le[i][r]-le[i][l-1])+f2[i-1][1];
            b2[l]=max(b2[l],b3[r+2]+f2[i][2]);
        }
    }
    
    _rep(j,m,1)b2[j]=max(b2[j],b2[j+1]);
    
    //rep(i,1,m)printf("%d ",b2[i]);printf("\n");
    
    CL(f,200);CL(g,200);ans=-1<<30;
    rep(j,1,m)
    {
        CL(g2,200);CP(f0,f);CL(f,200);
        rep(l,1,n)
        {
            int res=g[1][l-1][l-1];
            rep(r,l,n)
            {
                res=max(res,g[1][l][r]);
                f[0][l][r]=max(0,f0[0][l][r])+(up[r][j]-up[l-1][j]);
                f[1][l][r]=g[0][l][r+1]+(up[r][j]-up[l-1][j]);
                f[2][l][r]=res+(up[r][j]-up[l-1][j]);
                f[3][l][r]=max(f0[3][l][r],g[2][l+1][r])+(up[r][j]-up[l-1][j]);
                ans=max(ans,f[3][l][r]+b2[j+2]);
                
                g2[0][l][r]=f[0][l][r];
                g2[1][l][r]=max(f[1][l][r],f[2][l][r]);
                g2[2][l][r]=max(f[1][l][r],f[2][l][r]);
            }
        }
        CP(g,g2);
        rep(l,1,n)_rep(r,n,l)g[0][l][r]=max(g[0][l][r],g[0][l][r+1]);
        rep(l,1,n)rep(r,l,n)if(l-1<=r)g[1][l][r]=max(g[1][l][r],g[1][l-1][r]);
        _rep(l,n,1)rep(r,l,n)if(l+1<=r)g[2][l][r]=max(g[2][l][r],g[2][l+1][r]);
    }
    //f[j][1][l][r]=max(f[j-1][0][l][r+1..n])+(up[r][j]-up[l-1][j]);
                //f[j][1][l][r]=max(f[j-1][1][<=l][l-1..r])+(up[r][j]-up[l-1][j]);
                //f[j][2][l][r]=max(f[j-1][2][l][r],f[j-1][1][l+1..r][r])+(up[r][j]-up[l-1][j]);

    printf("%d\n",ans);
    scanf("\n");
    return 0;
}
