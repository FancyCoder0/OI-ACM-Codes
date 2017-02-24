#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<iostream>
#include<set>
using namespace std;
typedef long long int64;
typedef long double real;
#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

const int MAXN=110,MAXL=3;
int n,S1,S2,i,j,ans,tot1,time1[MAXN],num1[MAXN],time2[MAXN],num2[MAXN];

int a[MAXN][MAXN];

void search(int s1,int s2,int tot1,int tot2)
{
    int j,time0;
    if(tot1+tot2+(S1-s1+1)*time1[1]+(S2-s2+1)*time2[1]>=ans)return;
    if(s1>S1&&s2>S2){ans=tot1+tot2;return;}
    if(s1<=S1)
    rep(j,1,n)
    {
        time0=MAX(a[num1[j]][a[num1[j]][0]],tot1);
        a[num1[j]][++a[num1[j]][0]]=time0+time1[j];
        search(s1+1,s2,time0+time1[j],tot2);
        --a[num1[j]][0];
    }
    if(s2<=S2)
    rep(j,1,n)
    {
        time0=MAX(a[num2[j]][a[num2[j]][0]],tot2);
        a[num2[j]][++a[num2[j]][0]]=time0+time2[j];
        search(s1,s2+1,tot1,time0+time2[j]);
        --a[num2[j]][0];
    }
}

int main()
{
    freopen("jobs.in","r",stdin);
    freopen("jobs.out","w",stdout);
    int cases,number;
    scanf("%d",&cases);
    rep(number,1,cases)
    {
        scanf("%d%d%d",&n,&S1,&S2);
        rep(i,1,n)
        {
            scanf("%d",&time1[i]);num1[i]=i;
            scanf("%d",&time2[i]);num2[i]=i;
        }
        rep(i,1,n-1)
        rep(j,i+1,n)
        if(time1[i]>time1[j])swap(time1[i],time1[j]),swap(num1[i],num1[j]);
        
        rep(i,1,n-1)
        rep(j,i+1,n)
        if(time2[i]>time2[j])swap(time2[i],time2[j]),swap(num2[i],num2[j]);
        
        if(num1[1]!=num2[1]){printf("%d\n",time1[1]*S1+time2[1]*S2);continue;}
        n=MIN(n,MAXL);
        
        ans=1000000000;
        search(1,1,0,0);
        printf("%d\n",ans);
        
    }
    
    scanf("\n");
    return 0;
}
