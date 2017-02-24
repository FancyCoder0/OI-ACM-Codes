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
//#include<cmath>
using namespace std;

#define rep(i,x,y) for(i=x;i<=y;i++)
#define _rep(i,x,y) for(i=x;i>=y;i--)
#define CL(S,x) memset(S,x,sizeof(S))
#define mp make_pair
//#define x first
//#define y second
//#define MAX(x,y) ((x)>(y)?(x):(y))
//#define MIN(x,y) ((x)<(y)?(x):(y))
//#define sqr(x) ((x)*(x))

typedef long long int64;
typedef long double real;

int64 mod,a,c,x0,n,g,i,j;
struct mat
{
    int64 a[2][2];
    void clear(){memset(a,0,sizeof(a));}
}A,S;
int64 mul(int64 x,int64 y)
{
    int64 res=0;
    for(;y;y>>=1,x=(x+x)%mod)if(y&1)res=(res+x)%mod;
    return res;
}
mat operator*(mat a,mat b)
{
    mat c;c.clear();
    int i,j,k;
    rep(i,0,1)
    rep(j,0,1)
    rep(k,0,1)
    c.a[i][j]=(c.a[i][j]+mul(a.a[i][k],b.a[k][j]))%mod;
    return c;
}

int main()
{
    freopen("random.in","r",stdin);
    freopen("random.out","w",stdout);
    cin>>mod>>a>>c>>x0>>n>>g; 
    A.a[0][0]=a;A.a[0][1]=0;A.a[1][0]=c;A.a[1][1]=1;
    S.a[0][0]=x0;S.a[1][1]=1;
    for(;n;n>>=1,A=A*A)if(n&1)S=S*A;
    cout<<(S.a[0][0]+S.a[1][0])%mod%g<<endl;
        
    scanf("\n");
    return 0;
}
