/*
    Problem:
        棋盘黑白棋交替移动，求必胜态 
    Algorithm:
        黑白染色 建二分图 匹配 判点是否必须在匹配中
        S到右边（对应右边点开始的一种策略）
        T到左边（对应左边点开始的一种策略） 
    Note:
        使用了vector
        网络流没加双向边！
        建图判断时漏写！ 
*/
#include<cstdio>
#include<cstring>
#include<algorithm>

//#include<set>
#include<vector>
//#include<map>
//#include<string>
//#include<iomanip>
//#include<iostream>
//#include<cmath>
using namespace std;

#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
//#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define sqr(x) ((x)*(x))
#define mp make_pair
#define fi first
#define se second

typedef long long int64;
typedef long double real;

const int f1[]={0, 1,-1, 0, 0};
const int f2[]={0, 0, 0, 1,-1};
const int MAXN=1610,MAXM=13010,INF=1000000000;
int n,m,g,i,j,k,l,p,x,y,x0,y0,ed;
bool win,win0,win1;
char a[50][50];
int S,T,N,edge,vh[MAXN],h[MAXN],first[MAXN],last[MAXN],e[MAXM],b[MAXM],c[MAXM];
bool v[MAXN];
vector<int> P;
void clear(){edge=0;memset(first,-1,sizeof(first));memset(b,-1,sizeof(b));}
void add_(int x,int y,int z){e[edge]=y;c[edge]=z;if(first[x]==-1)first[x]=edge;else b[last[x]]=edge;last[x]=edge++;}
void add(int x,int y,int z){add_(x,y,z);add_(y,x,0);}

int ISAP(int i,int flow)
{
	if(i==T)return flow;
	int k,r=flow,d,minh=N;
	for(k=first[i];k>=0;k=b[k])
	if(c[k])
	{
		if(h[i]==h[e[k]]+1)
		{
			d=ISAP(e[k],MIN(flow,c[k]));
			c[k]-=d;c[k^1]+=d;r-=d;
			if(h[S]>=N)return flow-r;
			if(r==0)break;
		}
		minh=MIN(minh,h[e[k]]+1);
	}
	if(flow==r){if(--vh[h[i]]==0)h[S]=N;++vh[h[i]=minh];}
	return flow-r;
}
void dfs(int i,int kind)
{
    if(i==ed)
        if(((x0+y0)&1)==kind)win=0;
    v[i]=1;
    for(int k=first[i];k>=0;k=b[k])
    if(!v[e[k]]&&c[k]==kind)dfs(e[k],kind);
}
void work()
{
	memset(h,0,sizeof(h));
	memset(vh,0,sizeof(vh));
	vh[0]=N;
	while(h[S]<N)ISAP(S,INF);
	memset(v,0,sizeof(v));dfs(S,1);dfs(T,0);
}
bool pd(int x,int y){if(x<1||y<1||x>n||y>m)return 0;return 1;}
int num(int x,int y){return (x-1)*m+y;}
void jian(char kind)
{
    int i,j,t;
    clear();
    S=n*m+1;
    T=n*m+2;
    N=n*m+2;
    rep(t,1,4)
    if(pd(x0+f1[t],y0+f2[t]))
    if(a[x0+f1[t]][y0+f2[t]]==kind)
    if((x0+y0)&1)add(num(x0,y0),num(x0+f1[t],y0+f2[t]),1);
    else add(num(x0+f1[t],y0+f2[t]),num(x0,y0),1);
    
    rep(i,1,n)
    rep(j,1,m)
    if((i+j)&1)
    {
        add(S,num(i,j),1);
        rep(t,1,4)
        if(pd(i+f1[t],j+f2[t]))
        if((a[i][j]!='.')&&(a[i+f1[t]][j+f2[t]]!='.'))
        if((a[i][j]=='X')^(a[i+f1[t]][j+f2[t]]=='X'))
        add(num(i,j),num(i+f1[t],j+f2[t]),1);
    }
    else add(num(i,j),T,1);
}

int main()
{
    //freopen("game.in","r",stdin);
    //freopen("game.out","w",stdout);
    scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%s",a[i]+1);
	rep(i,1,n)
	rep(j,1,m)
	if(a[i][j]=='.')x0=i,y0=j;
	
	scanf("%d",&g);
	int ti;
	rep(ti,1,g)
	{
        win=1;ed=num(x0,y0);jian('O');work();win0=win;
        
		scanf("%d%d",&x,&y);
        swap(a[x0][y0],a[x][y]);
        x0=x;y0=y;
        if(win0)
        {
            win=1;ed=num(x0,y0);jian('X');work();
            if(win)P.push_back(ti);
        }
        
        scanf("%d%d",&x,&y);
        swap(a[x0][y0],a[x][y]);
        x0=x;y0=y;
    }    
	printf("%d\n",P.size());
	for(vector<int>::iterator pos=P.begin();pos!=P.end();pos++)printf("%d\n",*pos);
    scanf("\n");
    return 0;
}
