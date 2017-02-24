/*
    Problem:
    Algorithm:
    Note:
*/
#include<cstdio>
#include<cstring>
#include<set>
#include<vector>
using namespace std;

#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
int MAX(int x,int y){return (x)>(y)?(x):(y);}
//#define MIN(x,y) ((x)<(y)?(x):(y))

const int MAXN=200010;
const int INF=1000000000;

int edge,e[MAXN*2],b[MAXN*2],w[MAXN*2],first[MAXN],last[MAXN];
bool color[MAXN];
void clear(){edge=0;memset(first,-1,sizeof(first));memset(b,-1,sizeof(b));}
void add(int x,int y,int z){e[edge]=y;w[edge]=z;if(first[x]==-1)first[x]=edge;else b[last[x]]=edge;last[x]=edge++;}

int n,m,i,x,y,now,big,fa0,kind0,dis0,kong;
char c;

vector<int> ffa[MAXN];
vector<bool> fkind[MAXN];
vector<int> fdis[MAXN];
vector<int>::reverse_iterator pos1;
vector<bool>::reverse_iterator pos2;
vector<int>::reverse_iterator pos3;

multiset<int> s[MAXN*2][2];
int ro[MAXN*2][2];
int size[MAXN],st[MAXN],fa[MAXN],ans[MAXN*4];
bool done[MAXN*2];

int dfs0(int i,int f)
{
    st[++st[0]]=i;
    size[i]=1;fa[i]=f;
    for(int k=first[i];k>=0;k=b[k])
    if(!done[k]&&e[k]!=f)size[i]+=dfs0(e[k],i);
    return size[i];
}
void dfs(int i,int f,int dep,bool kind)
{
    ffa[i].push_back(now);
    fkind[i].push_back(kind);
    fdis[i].push_back(dep);
    
    if(color[i])
        s[now][kind].insert(dep);
    for(int k=first[i];k>=0;k=b[k])
    if(!done[k]&&e[k]!=f)dfs(e[k],i,dep+w[k],kind);
}
void updata(int bian)
{
    
    if(s[bian][0].size()==0||s[bian][1].size()==0)ans[bian]=-1;
    else ans[bian]=*s[bian][0].rbegin()+*s[bian][1].rbegin()+w[bian];
    ans[bian]=MAX(ans[bian],MAX(ans[ro[bian][0]],ans[ro[bian][1]]));
}
int work(int root)
{
    int i,k,min0=INF,size0,bian;
    st[0]=0;size0=dfs0(root,0);
    if(size0==1)    //leaf
    {
        ans[++kong]=color[root]-1;
        ffa[root].push_back(kong);
        fkind[root].push_back(0);
        fdis[root].push_back(ans[kong]);
        return kong;
    }
    
    rep(i,1,st[0])
    for(int k=first[st[i]];k>=0;k=b[k])
    if(!done[k]&&e[k]!=fa[st[i]])
    if(MAX(size[e[k]],size0-size[e[k]])<min0)
    min0=MAX(size[e[k]],size0-size[e[k]]),bian=k,ro[bian][0]=st[i],ro[bian][1]=e[k];
    
    done[bian]=done[bian^1]=1;
    now=bian;
    dfs(ro[bian][0],0,0,0);
    dfs(ro[bian][1],0,0,1);
    
    ro[bian][0]=work(ro[bian][0]);
    ro[bian][1]=work(ro[bian][1]);
    updata(bian);
    return bian;
}
char readc()
{
    char x;
    for(x=getchar();x<=32;x=getchar());
    return x;
}
int main()
{
    freopen("hide.in","r",stdin);
    freopen("hide.out","w",stdout);
    
    scanf("%d",&n);
    //改变树的形态 
    clear();
    rep(i,1,n-1)scanf("%d%d",&x,&y),add(x,y,1),add(y,x,1);
    memset(color,1,sizeof(color));
    
    kong=edge;
    big=work(1);
    
    scanf("%d",&m);
    rep(i,1,m)
    {
        c=readc();
        if(c=='G')printf("%d\n",ans[big]);
        else
        {
            scanf("%d",&x);
            color[x]=!color[x];
            for(pos1=ffa[x].rbegin(),
                pos2=fkind[x].rbegin(),
                pos3=fdis[x].rbegin();
                pos1!=ffa[x].rend();
                pos1++,pos2++,pos3++)
            {
                fa0=*pos1;kind0=*pos2;dis0=*pos3;
                if(fa0>edge)ans[fa0]=color[x]-1;    //leaf
                else
                {
                    if(color[x])s[fa0][kind0].insert(dis0);
                    else s[fa0][kind0].erase(s[fa0][kind0].find(dis0));
                    updata(fa0);
                }
            }
        }
    }
    
    
    scanf("\n");
    return 0;
}
