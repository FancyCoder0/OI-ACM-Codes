#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,x,y) for(i=x;i<=y;i++)
#define rep_(i,x,y) for(i=x;i>=y;i--)
#define MAX(x,y) ((x)>(y)?(x):(y))
using namespace std;
struct bignum{int num,s[110];};
bignum operator+(bignum a,bignum b)
{
    bignum c;
    memset(c.s,0,sizeof(c.s));
    c.num=MAX(a.num,b.num);
    int i;
    rep(i,1,c.num)c.s[i]=a.s[i]+b.s[i];
    rep(i,1,c.num)c.s[i+1]+=c.s[i]/10,c.s[i]%=10;
    if(c.s[c.num+1])c.num++;
    return c;
}
bignum operator/(bignum a,int b)
{
    int i,x=0;
    rep_(i,a.num,1)
    {
        x=x*10+a.s[i];
        a.s[i]=x/b;
        x=x%b;
    }
    if(a.s[a.num]==0)a.num--;
    return a;
}
void print(bignum a)
{
    int i;
    rep_(i,a.num,1)printf("%d",a.s[i]);printf("\n");
}
bignum x,a1,a2;
char a[200];
int i,j,k,l,p;
int main()
{
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    int cases;
    scanf("%d",&cases);
    for(int number=1;number<=cases;number++)
    {
        scanf("%s",a);
        memset(x.s,0,sizeof(x.s));
        memset(a1.s,0,sizeof(a1.s));
        memset(a2.s,0,sizeof(a2.s));
        x.num=strlen(a);rep(i,0,x.num-1)x.s[i+1]=a[x.num-i-1]-'0';
        //while((x.s[1]+1)&1)x=x/2;
        a1.s[1]=1;
        a1.num=a2.num=1;
        while(x.num)
        {
            if(x.s[1]&1)a2=a2+a1;
            else a1=a1+a2;
            x=x/2;
            //print(x);
        }
        print(a2);
    }
    
    scanf("\n");
    return 0;
}
