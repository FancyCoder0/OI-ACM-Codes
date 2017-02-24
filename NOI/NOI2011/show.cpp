#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<vector>
#include<map>
#include<queue>
#include<string>
#include<bitset>
#include<iomanip>
#include<iostream>
#include<cmath>
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
#define pb push_back
#define COUT(S,x) cout<<fixed<<setprecision(x)<<S<<endl

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

template<class T> inline void read(T&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
template<class T> inline void read(T&x,T&y){read(x);read(y);}
template<class T> inline void read(T&x,T&y,T&z){read(x);read(y);read(z);}
inline char getc(){char c;for(c=getchar();c<=32;c=getchar());return c;}

const int N=210;
const int inf=int(2e9)+1;
int n,i,j,k,l,r,p,x,y,t,l0,r0,m0,ans;
pii a[N],A[N];int rr[N],ff[N],o[N],st[N],home[N],res[N];
int f[N][N][N][2],f2[N][N][N],G[N][N],Z[N][N];

bool check(int g)   //合并答案 
{
	rep(r,p+1,n+1)if(a[r].fi>=a[p].se)
	{
		int tt=0;rep(j,p+1,r-1)if(a[j].se<=a[r].fi)tt++;
		rep(j,0,n)if(G[j][r]>=0)
		{
            //两种合并方式 
			int j2=max(0,g-j-tt);	
			if(Z[j2][ff[r]]+G[j][r]>=g)return 1;
			j2=max(0,g-G[j][r]-tt);
			if(Z[j2][ff[r]]+j>=g)return 1;
		}
	}
	return 0;
}

bool cmp(int x,int y){return A[x]<A[y];}
int main()
{
    freopen("show.in","r",stdin);freopen("show.out","w",stdout);
    
	read(n);rep(i,1,n)read(A[i].fi,A[i].se),A[i].se+=A[i].fi;
	rep(i,1,n)st[i]=i;sort(st+1,st+1+n,cmp);
	rep(i,1,n)a[i]=A[st[i]];
	sort(a+1,a+1+n);a[n+1]=mp(inf,inf);
	rep(i,1,n)o[i]=a[i].se;sort(o+1,o+1+n);j=1;rep(i,2,n)if(o[i]!=o[i-1])o[++j]=o[i];o[0]=j;
	rep(i,1,n)rr[i]=lower_bound(o+1,o+1+o[0],a[i].se)-o;
	rep(i,1,n)ff[i]=upper_bound(o+1,o+1+o[0],a[i].fi)-o-1;ff[n+1]=o[0];
	
	CL(f,200);f[0][0][0][0]=0;
	rep(i,0,n-1)rep(j,0,i)rep(r,0,i)rep(t,0,1)if(f[i][j][r][t]>=0)
	{
		upmax(f[i+1][j][r][0],f[i][j][r][t]);
		upmax(f[i+1][j+1][(a[i+1].se>a[r].se)?i+1:r][1],f[i][j][r][t]);
		if(a[i+1].fi>=a[r].se)upmax(f[i+1][f[i][j][r][t]+1][i+1][1],j);
	}
	rep(j,0,n)rep(r,0,n)rep(t,0,1)upmax(ans,min(j,f[n][j][r][t]));	printf("%d\n",ans);
	
	CL(f2,200);f2[n+1][0][n+1]=0;
	_rep(i,n+1,2)rep(j,0,n+1-i)_rep(l,n+1,i)if(f2[i][j][l]>=0)
	{
		upmax(f2[i-1][j][l],f2[i][j][l]);
		upmax(f2[i-1][j+1][(a[i-1].fi<a[l].fi)?i-1:l],f2[i][j][l]);
		if(a[i-1].se<=a[l].fi)upmax(f2[i-1][f2[i][j][l]+1][i-1],j);
	}
	
	CL(G,200);rep(i,1,n+1)rep(j,0,n+1)_rep(l,n+1,i)upmax(G[j][l],f2[i][j][l]); //右边的最值 
	rep(p,1,n)
	{
		CL(Z,200);rep(j,0,n)rep(r,0,p)upmax(Z[j][rr[r]],f[p][j][r][1]);
		rep(j,0,n)rep(r,1,o[0])upmax(Z[j][r],Z[j][r-1]);_rep(j,n,0)rep(r,0,o[0])upmax(Z[j][r],Z[j+1][r]); //左边最值 
		for(l0=0,r0=ans;l0<r0;){int m0=(l0+r0+1)/2;if(check(m0))l0=m0;else r0=m0-1;}
		res[st[p]]=l0;
	}
	rep(i,1,n)printf("%d\n",res[i]);
    return 0;
}
