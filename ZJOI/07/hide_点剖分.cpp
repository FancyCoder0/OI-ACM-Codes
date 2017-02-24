/*
    Problem:
        一颗树，节点01颜色，支持修改和询问最远的两个黑点 
    Algorithm:
        点分 
    Note:
        好难写。。。。
        点分求最值一般要记下①子树中的最优值和②路径过当前根的最值 等其他
        修改从深到浅，先修改由其他信息得来的信息，再修改最基本的信息 
*/ 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<string>
#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define mp make_pair
#define fi first
#define se second
using namespace std;

const int INF=1000000000;
const int MAXN=100001;
int n,m,i,edge,root,start,now,dep,Be,ins;
typedef int arr[MAXN];
int e[MAXN<<1],b[MAXN<<1],w[MAXN<<1];
arr first,last,dg,st,size,ans,belong;
char c;
bool done[MAXN],color[MAXN];
vector<int> belong_[MAXN]; 
vector<int> dis[MAXN];
vector<int> fa[MAXN];
map<int,multiset<int> > child[MAXN];
multiset<int> chm[MAXN];//记下每个子树的最值 
multiset<int> lk[MAXN];//记下每个点所有子树的最深度
map<int,multiset<int> >::iterator v;
void add(int x,int y,int z)
{
    e[edge]=y;w[edge]=z;
    if(first[x]==-1)first[x]=edge;
    else b[last[x]]=edge;
    last[x]=edge++;
}
int dfs(int i,int fa,int dep)
{
    if(fa>0)
        if(fa==st[1])belong[i]=i;
        else belong[i]=belong[fa];
    else belong[i]=0;
    st[++st[0]]=i;size[i]=1;dg[i]=dep;
    int k;
    for(k=first[i];k>=0;k=b[k])
    if(e[k]!=fa&&!done[e[k]])
    size[i]+=dfs(e[k],i,dep+w[k]);
    return size[i];
}
void pup(int now)
{
    switch(lk[now].size())
    {
        case 0:
            ans[now]=-1;
            break;
        case 1:
            ans[now]=0;
            break;
        default:
            ans[now]=*lk[now].rbegin()+*(++lk[now].rbegin());
            break;
    }
    if(chm[now].size()>0)ans[now]=MAX(ans[now],*(chm[now].rbegin()));
}
int work(int now)
{
    st[0]=0;dfs(now,0,0);
    int i,k,tmp,min,size0=size[now];
    min=INF;
    rep(i,1,st[0])
    {
        tmp=size0-size[st[i]];
        for(k=first[st[i]];k>=0;k=b[k])
        if(size[e[k]]<size[st[i]])tmp=MAX(tmp,size[e[k]]);
        if(tmp<min){min=tmp;now=st[i];}
    }
    st[0]=0;dfs(now,0,0);
    rep(i,1,st[0])
    {
        fa[st[i]].push_back(now);
        dis[st[i]].push_back(dg[st[i]]);
        belong_[st[i]].push_back(belong[st[i]]);
    }
    
    rep(i,1,st[0])
        child[now][belong[st[i]]].insert(dg[st[i]]);
    for(v=child[now].begin();v!=child[now].end();v++)
    lk[now].insert(*(v->se.rbegin())); 
    
    done[now]=1;
    for(k=first[now];k>=0;k=b[k])
    if(!done[e[k]])chm[now].insert(ans[work(e[k])]);
    pup(now);
    return now;
}
int main()
{
    freopen("hide.in","r",stdin);
    freopen("hide.out","w",stdout);
    scanf("%d\n",&n);
    edge=0;memset(first,-1,sizeof(first));memset(b,-1,sizeof(b));
    int x,y;rep(i,1,n-1){scanf("%d%d\n",&x,&y);add(x,y,1);add(y,x,1);}
    memset(color,1,sizeof(color));
    root=work(1);
    scanf("%d\n",&m);
    int number;
    vector<int>::reverse_iterator pos1,pos2,pos3;
    int lastadd,lastclear;
    rep(number,1,m)
    {
        c=getchar();
        if(c=='G')printf("%d\n",ans[root]);
        else
        {
            scanf("%d",&start);
            lastadd=lastclear=-INF;
            for(pos1=fa[start].rbegin(),pos2=dis[start].rbegin(),pos3=belong_[start].rbegin();
                pos1!=fa[start].rend();pos1++,pos2++,pos3++)
            {
                now=(*pos1);dep=(*pos2);Be=(*pos3);
                if(child[now][Be].size()>0)
                lk[now].erase(lk[now].find(*(child[now][Be].rbegin())));

                if(color[start])child[now][Be].erase(child[now][Be].find(dep));
                else child[now][Be].insert(dep);
                
                if(child[now][Be].size()>0)
                lk[now].insert(*(child[now][Be].rbegin()));

                if(lastclear!=-INF)chm[now].erase(chm[now].find(lastclear));
                if(lastadd!=-INF)chm[now].insert(lastadd);
                lastclear=ans[now];
                pup(now);
                lastadd=ans[now];
            }
            color[start]=!color[start];
        }
        scanf("\n");
        
    }
    
    scanf("\n");
    return 0;
} 
