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
#include<complex>
#include<ctime>
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

typedef long long ll;
typedef long double ld;
void read(int&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
char getc(){char c;for(c=getchar();c<=32;c=getchar());return c;}

const int N=200010;
int n,i,j,k,l,p;ld ans;
int d[N],b[N],hd[N],hb[N],mi[N],ma[N];bool can[N];

int main()
{ 
    //freopen("count.in","r",stdin);
    //freopen("count.out","w",stdout);
    read(n);
    rep(i,1,n)read(d[i]),hd[d[i]]=i;
    rep(i,1,n)read(b[i]),hb[b[i]]=i;
    
    rep(i,1,n)ma[i]=max(ma[i-1],hd[b[i]]);
    mi[n+1]=N;_rep(i,n,1)mi[i]=min(mi[i+1],hd[b[i]]);
    
    ans=2;
    rep(i,2,n-1)
    {
        if(hd[b[i]]>hd[b[i+1]])ans++;
        else if(hd[b[i]]+1==hd[b[i+1]]&&ma[i]<=hd[b[i+1]]&&mi[i]>=hd[b[i]])can[i]=1;
    }
    for(i=n-1;i>=2&&hd[b[i]]+1==hd[b[i+1]];i--)can[i]=1;
    rep(i,1,n)if(can[i])ans+=0.5;
    cout<<fixed<<setprecision(3)<<ans-0.001<<endl<<ans<<endl<<ans+0.001<<endl;
    //cout<<fixed<<setprecision(3)<<ans<<endl;
    
    scanf("\n");
    return 0;
}
