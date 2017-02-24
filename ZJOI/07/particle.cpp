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
typedef long double real;

const real inf=1e100;
const real eps=1e-8;
struct node{real x,y;};
struct vet{real x,y;};
real Rx,Ry,R,ans;node a[1100];vet v[1100];
int n,K,i,j,k,l;


vet solve(real A,real B,real c,real d,real a,real b)
{
    return (vet){(b*A-d*B)/(b*c-a*d),(a*A-c*B)/(a*d-b*c)};
}
vet fan(vet V,vet K)
{
    vet F;
    if(abs(K.y)<eps)F=(vet){-K.y/K.x,1};else F=(vet){1,-K.x/K.y};
    return solve(V.x*F.x+V.y*F.y,-(V.x*K.x+V.y*K.y),F.x,F.y,K.x,K.y);
}

real mindist(real A,real B,real C,real maxt)//两粒子最短距离 
{
    if(abs(A)<=eps)
    if(B<0)return maxt*B+C;else return C;
    real ans=min(C,A*maxt*maxt+B*maxt+C),xt=-B/(2*A);
    if(xt>=0&&xt<=maxt)ans=min(ans,A*xt*xt+B*xt+C);
    return sqrt(ans);
}
real jie(real A,real B,real C)
{
    if(abs(A)<=eps)return -C/B;
    return (-B+sqrt(B*B-4*A*C+eps))/(2*A);
}
real when_touch(node a,vet v)//粒子与圆相碰时间 
{
    return jie(sqr(v.x)+sqr(v.y),2*v.x*(a.x-Rx)+2*v.y*(a.y-Ry),sqr(a.x-Rx)+sqr(a.y-Ry)-sqr(R));
}
void move(node &a,vet v,real t){a.x+=v.x*t;a.y+=v.y*t;}
void reflect(node a,vet&v){v=fan(v,(vet){a.x-Rx,a.y-Ry});}

void calc(int I,int J)
{
    node i=a[I],j=a[J];vet vi=v[I],vj=v[J];
    int cnti=0,cntj=0;
    real tii,tij,minti;
    
    while(cnti<K&&cntj<K)
    {
        tii=when_touch(i,vi);
        tij=when_touch(j,vj);
        minti=min(tii,tij);
        ans=min(ans,mindist(sqr(vi.x-vj.x)+sqr(vi.y-vj.y),2*(i.x-j.x)*(vi.x-vj.x)+2*(i.y-j.y)*(vi.y-vj.y),sqr(i.x-j.x)+sqr(i.y-j.y),minti));
        
        move(i,vi,minti);
        move(j,vj,minti);
        if(abs(tii-minti)<eps)cnti++,reflect(i,vi);
        if(abs(tij-minti)<eps)cntj++,reflect(j,vj);
    }
}

int main()
{
    freopen("particle.in","r",stdin);
    freopen("particle.out","w",stdout);
    cin>>Rx>>Ry>>R;
    cin>>n>>K;
    rep(i,1,n)cin>>a[i].x>>a[i].y>>v[i].x>>v[i].y;
    
    ans=inf;
    rep(i,1,n)
    rep(j,i+1,n)
    calc(i,j);
    
    cout<<fixed<<setprecision(3)<<ans<<endl;
    scanf("\n");
    return 0;
}
