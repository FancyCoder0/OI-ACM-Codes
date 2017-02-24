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

typedef long long ll;
typedef long double ld;
void read(int&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
char getc(){char c;for(c=getchar();c<=32;c=getchar());return c;}

const int N=1000010;
const int mod=19940417;
int n,m,k,i,j,l,p,t;ll d,res,tmp,ans2; 
struct node{int i,f;}a[N];
bool cmp(node a,node b){return a.i<b.i;}

ll pow(ll a,ll b,ll c){ll ans=1;a%=c;for(;b;b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;return ans;}

ll f[N][2];
#define up(x,y) x=((x)+(y))%mod

int main()
{
    freopen("reminiscence.in","r",stdin);
    freopen("reminiscence.out","w",stdout);
	read(n);read(m);
	rep(i,1,m)read(a[i].i),read(a[i].f);
	sort(a+1,a+1+m,cmp);
	
	j=0;rep(i,1,m)if(mp(a[i].i,a[i].f)!=mp(a[i-1].i,a[i-1].f))a[++j]=a[i];m=j;
	
	rep(i,1,m)if(a[i].i==a[i-1].i&&a[i].f!=a[i-1].f){printf("0 0\n");return 0;}
	if(a[i].i==n&&a[i].f!=0){printf("0 0\n");return 0;}
	
	if(a[m].i!=n)a[++m]=(node){n,0};
	
	rep(i,1,m)upmax(ans2,1LL*a[i].f);
	
	f[0][0]=1;
	rep(i,0,m-1)
	{
		//cout<<i<<':'<<f[i][0]<<' '<<f[i][1]<<endl;
		
		d=a[i+1].i-a[i].i-a[i].f-a[i+1].f;
		
		
		//上-》上 
		
		if(f[i][0])if(d>0&&d%2==0)upmax(ans2,a[i].f+(d/2));
		
		res=0;
		
			if(d>0&&d%2==0)res=pow(2,d/2-1,mod);
			if(a[i].f+(a[i+1].i-a[i].i)==a[i+1].f)res++;
			up(f[i+1][0],f[i][0]*res);
			
		
		//上-》下 
		tmp=a[i+1].f-a[i].f+(a[i+1].i-a[i].i);if(f[i][0]&&tmp%2==0)upmax(ans2,a[i].f+tmp/2);
		
		res=0;
		if(d>=0&&d%2==0)res=pow(2LL,d/2,mod)-1;
		if(((a[i+1].f-a[i].f)&1)^((a[i+1].i-a[i].i)&1)==0)
		{
			if(a[i].f<a[i+1].f)res+=(a[i].f+(a[i+1].i-a[i].i)>=a[i+1].f); 
			else res+=(a[i].f-(a[i+1].i-a[i].i)<a[i+1].f);
		}
		if(a[i+1].f>0)up(f[i+1][1],f[i][0]*res);
		
		//下-》上 
		if(f[i][1])if(d%2==0&&d>=0)upmax(ans2,d/2);
		
		res=0;
		
			if(d%2==0)
			if(d>0)res=pow(2,d/2-1,mod);
			else if(d==0)res=1;
			up(f[i+1][0],f[i][1]*res);
		
		
		//下-》下 
		if(f[i][1])if(d%2==0&&d>=0)upmax(ans2,d/2);
		
		res=0;
		if(d>=0&&d%2==0)res=pow(2LL,d/2,mod);
		if(a[i].f-(a[i+1].i-a[i].i)==a[i+1].f)res++;
		if(a[i+1].f>0)up(f[i+1][1],f[i][1]*res);
		
		
	}
	
	cout<<f[m][0]<<' '<<ans2<<endl;
    scanf("\n");
    return 0;
}
