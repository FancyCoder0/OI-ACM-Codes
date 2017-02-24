#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define rep(i,x,y) for(i=x;i<=y;i++)
#define sqr(x) ((x)*(x))
typedef double real;

const int MAXN=10010;
const real zero=1e-12;
int n,i;real E,l,r,mid,ans;
real s[MAXN],k[MAXN],v0[MAXN],maxv[MAXN],v[MAXN];
inline bool ok()
{
    real a,b,c,d,l,r,x,total=0;
    rep(i,1,n)
    {
        a=2*mid*k[i];b=-a*v0[i];c=0;d=1;
        for(l=max(v0[i],real(0)),r=maxv[i];x=(l+r)/2,r-l>zero;)
        if(a*x*x*x+b*x*x+c*x+d>0)l=x;else r=x;
        v[i]=(l+r)/2;
        total+=sqr(v[i]-v0[i])*s[i]*k[i];
    }
    return total<E;
}
int main()
{
    freopen("bicycling.in","r",stdin);
    freopen("bicycling.out","w",stdout);
    scanf("%d%lf",&n,&E);
    rep(i,1,n)scanf("%lf%lf%lf",&s[i],&k[i],&v0[i]);
    
    rep(i,1,n)maxv[i]=((s[i]>0)?sqrt(E/s[i]/k[i]):0)+v0[i];
    rep(i,1,n)r=min(r,-1/(2*k[i]*(maxv[i]-v0[i])*sqr(maxv[i])));
    for(l=-1000,r=0;mid=(l+r)/2,r-l>zero;)if(ok())l=mid;else r=mid;
    
    rep(i,1,n)ans+=s[i]/v[i];
    printf("%.8lf\n",ans);
    return 0;
}
