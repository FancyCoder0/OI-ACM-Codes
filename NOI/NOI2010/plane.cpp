#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define rep(i,x,y) for(i=x;i<=y;i++)
using namespace std;
const int MAXN=2010;
const int MAXM=100000;
int MAX(int x,int y){return x>y?x:y;}
int MIN(int x,int y){return x<y?x:y;}
int n,m,i,j,k,l,p,ans,cnt;
int a[MAXN],pp[MAXN],edge,e[MAXM],b[MAXM],first[MAXN],last[MAXN],min[MAXN],q[MAXN],d[MAXN],num[MAXN];
bool v[MAXN];
set<int> c[MAXN];
void clear(){edge=0;memset(first,-1,sizeof(first));memset(b,-1,sizeof(b));};
void add(int x,int y){d[y]++;e[edge]=y;if(first[x]==-1)first[x]=edge;else b[last[x]]=edge;last[x]=edge++;}
int dfs(int i)
{
	v[i]=1;
	int ans=1;
	for(int k=first[i];k>=0;k=b[k])
	if(!v[e[k]])ans+=dfs(e[k]);
	return ans;
}

int main()
{
    scanf("%d%d",&n,&m);
    rep(i,1,n)scanf("%d",&a[i]),c[a[i]].insert(i);
	/*
	bool print=1;
    rep(i,1,n)
    for(set<int>::iterator pos=c[i].begin();pos!=c[i].end();pos++)
    if(print)print=0,printf("%d",*pos);else printf(" %d",*pos);printf("\n");
    */
    clear();
    int x,y;
    rep(i,1,m)scanf("%d%d",&x,&y),add(y,x);
    rep(i,1,n)if(first[i]==-1)add(i,0);
    //printf("OK!\n");
    int head=1,tail=0;
    rep(i,1,n)if(d[i]==0)q[++tail]=i;
    while(head<=tail)
    {
    	for(int k=first[q[head]];k>=0;k=b[k])
    	{
    		a[e[k]]=MIN(a[e[k]],a[q[head]]-1);
    		if(--d[e[k]]==0)q[++tail]=e[k];
    	}
    	head++;
    }
    
    rep(i,1,n)num[i]=i; 
    rep(i,1,n-1)
    rep(j,i+1,n)
    if(a[i]>a[j]){swap(a[i],a[j]),swap(num[i],num[j]);}
    rep(i,1,n-1)printf("%d ",num[i]);printf("%d\n",num[n]);
    rep(i,1,n)
    {
    	memset(v,0,sizeof(v));
    	ans=cnt=dfs(i)-1;
    	
    	rep(j,1,n)
    	if(!v[num[j]])
    	{
    		cnt++;
    		if(a[j]<=ans)ans++;
    		else if(cnt>a[j])ans=a[j]+1;
    	}
    	if(i>1)printf(" ");printf("%d",ans);
    }  	
    printf("\n");
    
    
    
    scanf("\n");
    return 0;
}
