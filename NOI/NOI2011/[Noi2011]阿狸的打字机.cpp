/*
    Problem:
        [Noi2011]阿狸的打字机
    Algorithm:
        AC自动机建树 对fail指针反向 问题转化为求子树和
        由于询问在同一根链上，所以可以通过dfs序+树状数组解决
        离线O(N*kind(26)+MlogN) 
    Note:
        AC自动机还是蛮短的。 
        注意单词重复的情况！（虽然还是可以A） 
*/
#include<cstdio>
#include<cstring>
#include<algorithm>

//#include<set>
//#include<vector>
//#include<map>
//#include<string>
//#include<iomanip>
//#include<iostream>
//#include<cmath>
using namespace std;

#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
//#define MAX(x,y) ((x)>(y)?(x):(y))
//#define MIN(x,y) ((x)<(y)?(x):(y))
//#define sqr(x) ((x)*(x))
//#define mp make_pair
//#define x first
//#define y second

const int MAXN=100010;
typedef long long int64;
typedef long double real;

int n,m,i,j,k,l,p,x,y;
char s[MAXN];
int tot,map[MAXN][26],fail[MAXN],pre[MAXN],q[MAXN];
int ask[MAXN],ans[MAXN];
int st[MAXN],head[MAXN],tail[MAXN];

struct list
{
    int edge,first[MAXN],last[MAXN],e[MAXN*2],b[MAXN*2];
    void clear(){edge=0;memset(first,-1,sizeof(first));memset(b,-1,sizeof(b));}
    void add(int x,int y){e[edge]=y;if(first[x]==-1)first[x]=edge;else b[last[x]]=edge;last[x]=edge++;}
}qu,g,end;

struct tr
{
    int sum[MAXN];
    int ask(int i)
    {
        int ans=0;
        for(ans=0;i;i-=i&(-i))ans+=sum[i];
        return ans;
    }
    void add(int i,int s)
    {
        for(;i<=st[0];i+=i&(-i))sum[i]+=s;
    }
}a;


void buildAC()
{
    int i,j,k,u,v,now=1,have=0;
    tot=1;
    rep(i,1,n)
    {
        switch(s[i])
        {
            case 'P':
                ask[++have]=now;
                end.add(now,have);
                break;
            case 'B':now=pre[now];  
                break;
            default:
                now=map[now][s[i]-'a']==0?pre[++tot]=now,map[now][s[i]-'a']=tot:map[now][s[i]-'a'];
                break;
        }
    }
    q[i=j=1]=1;
    for(;i<=j;i++)
    {
        u=q[i];v=fail[q[i]];
        rep(k,0,25)
        if(map[u][k])
        {
            q[++j]=map[u][k];
            fail[q[j]]=(u==1)?1:map[v][k];
            g.add(fail[q[j]],q[j]);
        }
        else map[q[i]][k]=(u==1)?1:map[v][k];
    }
}
void dfs(int i)
{
    st[++st[0]]=i;head[i]=st[0];
    for(int k=g.first[i];k>=0;k=g.b[k])dfs(g.e[k]);
    tail[i]=st[0];
}

void work()
{
    int i,k,k0,now=1;
    rep(i,1,n)
    {
        if(s[i]=='P')continue;
        if(s[i]=='B')a.add(head[now],-1),now=pre[now];
        else now=map[now][s[i]-'a'],a.add(head[now],1);
        
        for(k0=end.first[now];k0>=0;k0=end.b[k0])
            for(k=qu.first[end.e[k0]];k>=0;k=qu.b[k])
            ans[k]=a.ask(tail[ask[qu.e[k]]])-a.ask(head[ask[qu.e[k]]]-1);
    }
    
}

int main()
{
    qu.clear();g.clear();end.clear();
    scanf("%s",s+1);
    n=strlen(s+1);
    scanf("%d",&m);
    rep(i,1,m)scanf("%d%d",&x,&y),qu.add(y,x);
    buildAC();
    dfs(1);
    work();
    
    rep(i,0,m-1)printf("%d\n",ans[i]);
    scanf("\n");
    return 0;
}
