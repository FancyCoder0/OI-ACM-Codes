#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<iomanip>
#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

#define rep(i,x,y) for(i=(x);i<=(y);i++)
#define _rep(i,x,y) for(i=(x);i>=(y);i--)
#define REP(i,x,y) for(int i=(x);i<=(y);i++)
#define _REP(i,x,y) for(int i=(x);i>=(y);i--)
#define mp make_pair
#define fi first
#define se second
#define CL(S,x) memset(S,x,sizeof(S))
#define CP(S1,S2) memcpy(S1,S2,sizeof(S2))
#define ALL(it,S) for(it=S,begin();it!=S.end();it++)
#define abs(x) ((x)>0?(x):(-(x)))
#define sqr(x) ((x)*(x))
#define upmax(x,y) x=max(x,y)
#define upmin(x,y) x=min(x,y)

typedef long long ll;
typedef long double ld;

void read(int&x){char c;bool f=0;for(c=getchar();c<=32;c=getchar());if(c=='-')f=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+(c-'0');if(f)x=-x;}
void read(int&x,int&y){read(x);read(y);}
void read(int&x,int&y,int&z){read(x);read(y);read(z);}
char getc(){char c;for(c=getchar();c<=32;c=getchar());return c;}

const int inf=int(1e9);
int a,all,n,i,j,k,l,p,x,y,z,AS,BS,CS;
int op[11];

struct node{int g,tot,all,a[75][3];}cc[11][8];

int v[500010],e[500010][10];

int A[500010],B[500010],C[500010];
int q[500010];
int have[75][75][75];

void bfs(int s,int*d)
{
    int i,j,k,l,p,u,v;
    
    rep(i,1,all)d[i]=inf;
    q[1]=s;d[s]=0;
    for(i=j=1;i<=j;i++)
    {
        u=q[i];
        rep(k,1,e[u][0])
        {
            v=e[u][k];
            if(d[u]+1<d[v])
            {
                d[v]=d[u]+1;
                q[++j]=v;
            }
        }
    }
}

const int dx[]={1,-1,0,0,0,0};
const int dy[]={0,0,1,-1,0,0};
const int dz[]={0,0,0,0,1,-1};
int c[75][75][75],cnt[75][75][75];
int g,li[11][3];
int ans0=inf,ans1=0;
int pp[11];

int tott;

void dfs(int dep,int tot)
{
	if(tot>=ans0&&tot+op[dep]<=ans1)return;
	
    if(dep>g)
    {
        upmin(ans0,tot);
        upmax(ans1,tot);
        return;
    }
    int t,i;
    rep(t,0,5)
    {
        pp[dep]=t;
        
        rep(i,1,cc[dep][t].g)
        {
            x=cc[dep][t].a[i][0];
            y=cc[dep][t].a[i][1];
            z=cc[dep][t].a[i][2];
            if(++cnt[x][y][z]==1)tot+=c[x][y][z];
        }
        dfs(dep+1,tot+cc[dep][t].tot);
        
        rep(i,1,cc[dep][t].g)
        {
            x=cc[dep][t].a[i][0];
            y=cc[dep][t].a[i][1];
            z=cc[dep][t].a[i][2];
            if(--cnt[x][y][z]==0)tot-=c[x][y][z];
        }
    }
}


int main()
{
    freopen("glitter.in","r",stdin);
    freopen("glitter.out","w",stdout);
    
    scanf("%d\n",&a);all=a*a*a;
    rep(z,1,all)
    {
        bool fir=1;int x=0;
        char c;
        for(c=getchar();!(c>='0'&&c<='9');c=getchar());
        while(1)
        {
            if(c==' ')
            {
                if(fir)v[z]=x,fir=0;
                else e[z][++e[z][0]]=x;
                x=0;
            }
            else if(c>='0'&&c<='9')x=x*10+(c-'0');
            else break;
            c=getchar();
        }
        if(x)e[z][++e[z][0]]=x;
        if(e[z][0]==3)AS=z;
    }
    
    bfs(AS,A);
    
    
    rep(i,1,all)
    if(A[i]==a-1&&e[i][0]==3)
    if(BS==0)BS=i;else CS=i;
    
    bfs(BS,B);
    bfs(CS,C);
    
    rep(i,1,all)
    {
        int aa=A[i]+3,bb=B[i]+2,cc=C[i]+2;
        z=(bb+cc-2*a)/2;
        y=(aa+bb-a)/2-z;
        x=aa-y-z;
        c[x][y][z]=v[i];
        if(v[i]==0)
        {
            ++g;
            li[g][0]=x;
            li[g][1]=y;
            li[g][2]=z;
        }
    }
    
    int t0,t1,T=0;
    
rep(i,1,g)rep(t0,0,5)
{
    ++T;
    rep(j,1,g)if(i!=j)
    rep(t1,0,5)
    {
        x=li[j][0];y=li[j][1];z=li[j][2];
        while(1){
            x+=dx[t1];y+=dy[t1];z+=dz[t1];
            if(x<1||y<1||z<1||x>a||y>a||z>a)break;
            cnt[x][y][z]=T;
        }
    }
    
        x=li[i][0];y=li[i][1];z=li[i][2];
        while(1){
            x+=dx[t0];y+=dy[t0];z+=dz[t0];
            if(x<1||y<1||z<1||x>a||y>a||z>a)break;
            if(cnt[x][y][z]==T)
            {
                int r=++cc[i][t0].g;
                cc[i][t0].a[r][0]=x;
                cc[i][t0].a[r][1]=y;
                cc[i][t0].a[r][2]=z;
                cc[i][t0].all+=c[x][y][z];
            }
            else
			{
				cc[i][t0].all+=c[x][y][z];
				cc[i][t0].tot+=c[x][y][z];
			}
        }
    //if(cc[i][t0].g)printf("%d\n",cc[i][t0].g);
}
    _rep(i,g,1)
    {
		int best=0;
		rep(t0,0,5)upmax(best,cc[i][t0].all);
		op[i]=op[i+1]+best;
	}
    
    CL(cnt,0);
    dfs(1,0);
    //printf("%d\n",tott);
    printf("%d %d\n",ans0,ans1);
    
    scanf("\n");
    return 0;
}
