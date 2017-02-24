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
using namespace std;

#define rep(i,x,y) for(i=x;i<=y;i++)
#define _rep(i,x,y) for(i=x;i>=y;i--)
#define CL(S,x) memset(S,x,sizeof(S))
#define CP(S1,S2) memcpy(S1,S2,sizeof(S2))
#define ALL(x,S) for(x=S.begin();x!=S.end();x++)
#define mp make_pair
#define sqr(x) ((x)*(x))
//#define x first
//#define y second
//#define MAX(x,y) ((x)>(y)?(x):(y))
//#define MIN(x,y) ((x)<(y)?(x):(y))


typedef long long int64;
typedef long double real;


const int MAXN=100010;
const int MAXD=4501000;
int R,C,n,i,j,k,x,y,root;int64 ans;
vector<int> a[40010];
vector<int>::iterator it;
int N,l[MAXD],r[MAXD],h[MAXD],first[MAXD],next[MAXD];
int64 sum[MAXD];

int build(int i,int L,int R,int H){l[i]=L;r[i]=R;h[i]=H;sum[i]=1LL*(R-L+1)*(R-L+2)/2*H;return i;}
void calc(int i){sum[i]=1LL*(r[i]-l[i]+1)*(r[i]-l[i]+2)/2*h[i];for(int son=first[i];son;son=next[son])sum[i]+=sum[son];}
void addh(int i){h[i]++;sum[i]+=1LL*(r[i]-l[i]+1)*(r[i]-l[i]+2)/2;}
void addson(int i,int s){next[s]=first[i];first[i]=s;sum[i]+=sum[s];}
void optimize(int i)
{
    if(first[i]&&l[first[i]]==l[i]&&r[first[i]]==r[i])
    h[i]+=h[first[i]],first[i]=first[first[i]];
}

void split(int i,int c,int* news)
{
    for(int prev=0,son=first[i];son;prev=son,son=next[son])
    if(l[son]<=c&&c<=r[son])
    {
        sum[i]-=sum[son];
        if(prev)next[prev]=next[son];else first[i]=next[son];
    
        int newson[2]={0,0};split(son,c,newson);
        for(int k=0;k<2;k++)if(newson[k])addson(i,newson[k]);
        break;
    }
    
    if(h[i]==0)return;
    if(l[i]<c)news[0]=build(++N,l[i],c-1,h[i]);
    if(r[i]>c)news[1]=build(++N,c+1,r[i],h[i]);
    
    for(int son=first[i],nextson;son;son=nextson)
    {
        nextson=next[son];
        addson(news[l[son]>c],son);
    }
    
    for(int k=0;k<2;k++)if(news[k])optimize(news[k]);
}

int main()
{
    freopen("mrx.in","r",stdin);
    freopen("mrx.out","w",stdout);
    
    scanf("%d%d%d",&R,&C,&n);
    rep(i,1,n)scanf("%d%d",&x,&y),a[x].push_back(y);
    
    root=build(++N,1,C,0);
    
    ans=1LL*R*(R+1)*C*(C+1)/4;
    rep(i,1,R)
    {
        addh(root);
        ALL(it,a[i])
        {
            int newson[2]={0,0};
            if(h[root]==0)split(root,*it,newson);
            else
            {
                split(root,*it,newson);
                root=build(++N,1,C,0);
                for(int k=0;k<2;k++)if(newson[k])addson(root,newson[k]);
                calc(root);
            }
        }
        ans-=sum[root];
    }
    cout<<ans<<endl;

    scanf("\n");
    return 0;
}
