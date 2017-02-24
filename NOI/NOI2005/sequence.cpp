#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,x,y) for(i=x;i<=y;i++)
using namespace std;


const int MAXN=510000;
const int INF=2000000000;
int n,m,i,j,k,l,p,pos,tot,c;
char str[20];
int a[MAXN];
int MAX(int x,int y){return x>y?x:y;}


struct splay
{
    int N,root;
    int l[MAXN],r[MAXN],fa[MAXN],size[MAXN],s[MAXN],sum[MAXN],same[MAXN],
        max[MAXN],maxl[MAXN],maxr[MAXN],maxs[MAXN];
    bool rev[MAXN];
    int head,tail,st[MAXN*8];
    
    
    void prev(int i)
    {
        rev[i]=!rev[i];
        swap(maxl[i],maxr[i]);
        swap(l[i],r[i]);
    }
    void psame(int i,int x)
    {
        same[i]=x;
        max[i]=s[i]=x;
        sum[i]=x*size[i];
        maxl[i]=maxr[i]=maxs[i]=x>0?sum[i]:0;
    }
    void pdown(int i)
    {
        if(rev[i])
        {
            if(l[i])prev(l[i]);
            if(r[i])prev(r[i]);
            rev[i]=!rev[i];
        }
        if(same[i]!=INF)
        {
            if(l[i])psame(l[i],same[i]);
            if(r[i])psame(r[i],same[i]);
            same[i]=INF;
        }
    }
    void updata(int i)
    {
        size[i]=size[l[i]]+size[r[i]]+1;
        sum[i]=sum[l[i]]+sum[r[i]]+s[i];
        max[i]=MAX(s[i],MAX(max[l[i]],max[r[i]]));
        maxl[i]=MAX(maxl[l[i]],sum[l[i]]+s[i]+maxl[r[i]]);
        maxr[i]=MAX(maxr[r[i]],sum[r[i]]+s[i]+maxr[l[i]]);
        maxs[i]=MAX(MAX(maxs[l[i]],maxs[r[i]]),maxr[l[i]]+s[i]+maxl[r[i]]);
    }    
    void left(int i)
    {
        int x,y;
        x=r[i];
        y=l[x];
        r[i]=y;
        l[x]=i;
        if(y)fa[y]=i;
        if(fa[i])if(l[fa[i]]==i)l[fa[i]]=x;else r[fa[i]]=x;
        fa[x]=fa[i];
        fa[i]=x;
        updata(i);
        if(root==i)root=x;
    }
    void right(int i)
    {
        int x,y;
        x=l[i];
        y=r[x];
        l[i]=y;
        r[x]=i;
        if(y)fa[y]=i;
        if(fa[i])if(l[fa[i]]==i)l[fa[i]]=x;else r[fa[i]]=x;
        fa[x]=fa[i];
        fa[i]=x;
        updata(i);
        if(root==i)root=x;
    }
    void spl(int x,int f)
    {
        int y,z;
        pdown(x);
        while(fa[x]!=f)
        {
            y=fa[x];
            z=fa[y];
            if(z)pdown(z);
            if(y)pdown(y);
            if(z==f)
                if(l[y]==x)right(y);else left(y);
            else
                if(l[z]==y)
                    if(l[y]==x){right(z);right(y);}
                    else       { left(y);right(z);}
                else
                    if(l[y]==x){right(y); left(z);}
                    else       { left(z); left(y);}
        }
        updata(x);
    }
    void sel(int x,int f)
    {
        int t=root;
        pdown(t);
        while(x!=size[l[t]]+1)
        {
            if(x<size[l[t]]+1)t=l[t];
            else{x-=size[l[t]]+1;t=r[t];}
            pdown(t);
        }
        spl(t,f);
    }
    int tiqu(int x,int y)
    {
        if(x==1)
            if(y==N)return root;
            else{sel(y+1,0);return l[root];}
        else
            if(y==N){sel(x-1,0);return r[root];}
            else{sel(x-1,0);sel(y+1,root);return l[r[root]];}
    }
    void ins(int x,int y,int f,int kind)
    {
        int i;
        N++;
        if(head>tail)i=N;else{i=st[head++];if(l[i])st[++tail]=l[i];if(r[i])st[++tail]=r[i];}
        if(f==0)root=i;
        else
        if(kind==0)l[f]=i;else r[f]=i;
        l[i]=r[i]=0;same[i]=INF;rev[i]=0;fa[i]=f;s[i]=a[(x+y)/2];
        if(x<=(x+y)/2-1)ins(x,(x+y)/2-1,i,0);
        if((x+y)/2+1<=y)ins((x+y)/2+1,y,i,1);
        updata(i);
    }
    void del(int x)
    {
        if(l[fa[x]]==x)l[fa[x]]=0;else r[fa[x]]=0;
        updata(fa[x]);spl(fa[x],0);
        N-=size[x];
        st[++tail]=x;
    }
    
    void print(int x)
    {
        pdown(x);
        if(l[x])print(l[x]);
        printf("%d ",s[x]);
        if(r[x])print(r[x]);
        updata(x);
    }
}T;

int readn()
{
    char x;
    int ans=0;
    for(x=getchar();x<=32;ans=ans*10+x-'0',x=getchar());
    return ans;
}

int main()
{
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    T.head=1;T.tail=0;T.max[0]=-INF;
    scanf("%d%d",&n,&m);
    rep(i,1,n)scanf("%d",&a[i]);
    T.ins(1,n,0,0);
    
    rep(i,1,m)
    {
        scanf("%s",str);
        if(str[0]=='G')
        {
            scanf("%d%d",&pos,&tot);
            printf("%d\n",T.sum[T.tiqu(pos,pos+tot-1)]);
        }
        else
        if(str[0]=='M'&&str[3]=='-')
        {
            if(T.max[T.root]<0)printf("%d\n",T.max[T.root]);
            else printf("%d\n",T.maxs[T.root]);
        }
        else
        if(str[0]=='I')
        {
            scanf("%d%d",&pos,&tot);
            rep(j,1,tot)scanf("%d",&a[j]);
            if(pos==0){T.sel(1,0);T.ins(1,tot,T.root,0);T.updata(T.root);}
            else
            if(pos==T.N){T.sel(T.N,0);T.ins(1,tot,T.root,1);T.updata(T.root);}
            else{T.sel(pos,0);T.sel(pos+1,T.root);T.ins(1,tot,T.r[T.root],0);T.updata(T.r[T.root]);T.updata(T.root);}
        }
        else
        if(str[0]=='D')
        {
            scanf("%d%d",&pos,&tot);
            T.del(T.tiqu(pos,pos+tot-1));
        }
        else
        if(str[0]=='M'&&str[3]=='E')
        {
            scanf("%d%d%d",&pos,&tot,&c);
            T.psame(p=T.tiqu(pos,pos+tot-1),c);
            T.spl(p,0);
        }
        else
        if(str[0]=='R')
        {
            scanf("%d%d",&pos,&tot);
            T.prev(p=T.tiqu(pos,pos+tot-1));
            T.spl(p,0);
        }
        
        
        //if(str[0]!="R')
        //T.print(T.root);printf("\n");
    }
    
    scanf("\n");
    return 0;
}
