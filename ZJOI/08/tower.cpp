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

const int MAXN=310;
const real eps=1e-6;
struct line{real k,b;}yu[MAXN],l[MAXN],st[MAXN];
bool cmp(line a,line b){return a.k<b.k||(abs(a.k-b.k)<eps&&a.b>b.b);}
int n,i,j,k,p,top,N;real ans,x,a[MAXN],b[MAXN],t[MAXN];

real jiao(line a,line b){return (b.b-a.b)/(a.k-b.k);}

int main()
{
    freopen("tower.in","r",stdin);
    freopen("tower.out","w",stdout);
    cin>>n;
    rep(i,1,n)cin>>a[i];
    rep(i,1,n)cin>>b[i];
    rep(i,2,n)
    {
        l[++N].k=(b[i]-b[i-1])/(a[i]-a[i-1]);
        l[N].b=b[i]-l[N].k*a[i];
    }
    CP(yu,l);
    sort(l+1,l+1+N,cmp);
    
    rep(i,1,N)if(i==1||l[i].k!=l[i-1].k)
    {
        while(top>1&&jiao(st[top-1],st[top])>=jiao(st[top],l[i]))top--;
        st[++top]=l[i];
    }
    rep(i,1,top-1)t[i]=jiao(st[i],st[i+1]);t[top]=1e100;
    
    ans=1e10;
    rep(i,1,n)
    {
        p=lower_bound(t+1,t+1+top,a[i])-t;
        ans=min(ans,st[p].k*a[i]+st[p].b-b[i]);
    }
    rep(i,1,top-1)
    {
        p=(lower_bound(a+1,a+1+n,t[i])-a)-1;
        ans=min(ans,(t[i]*st[i].k+st[i].b)-(yu[p].k*t[i]+yu[p].b));
        
    }
    cout<<fixed<<setprecision(3)<<ans+eps<<endl;
    
    scanf("\n");
    return 0;
}
