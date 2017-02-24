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
#include<queue>
using namespace std;

#define rep(i,x,y) for(i=x;i<=y;i++)
#define _rep(i,x,y) for(i=x;i>=y;i--)
#define CL(S,x) memset(S,x,sizeof(S))
#define CP(S1,S2) memcpy(S1,S2,sizeof(S2))
#define ALL(x,S) for(x=S.begin();x!=S.end();x++)
#define sqr(x) ((x)*(x))
#define mp make_pair
#define fi first
#define se second
#define upmin(x,y) x=min(x,y)
#define upmax(x,y) x=max(x,y)

typedef long long int64;
typedef long double real;
void read(int64&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
char getc(){char c;for(c=getchar();c<=32;c=getchar());return c;}

const int L=1000050;
const int64 mod=1000000007LL;
int64 tmp[L];
struct big{
    int l,s[L];
    void read()
    {
        char c;
        for(c=getchar();c<=32;c=getchar());
        for(l=0;c>32;c=getchar())s[++l]=c-'0';
        reverse(s+1,s+1+l);
    }
    int div(int t)
    {
        int i;int64 x=0;
        _rep(i,l,1)
        {
            x=x*10+s[i];
            s[i]=x/t;
            x=x%t;
        }
        while(l>0&&s[l]==0)l--;
        return x%t;
    }
    void dec()
    {
        int i;
        s[1]--;
        for(i=1;s[i]<0;i++)s[i]+=10,s[i+1]--;
        while(l>0&&s[l]==0)l--;
    }
    void mul(int b)
    {
        int i;l+=20;
        rep(i,1,l)tmp[i]=1LL*s[i]*b;
        rep(i,1,l)tmp[i+1]+=tmp[i]/10,tmp[i]%=10;
        while(l>0&&tmp[l]==0)l--;
        rep(i,1,l)s[i]=tmp[i];
    }
};

big n,m,z;int64 a,b,c,d,p,q,x,P,Q;
int64 pow(int64 a,int64 b,int64 mod)
{
    int64 ans=1;
    for(;b;b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
    return ans;
}


int main()
{
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    n.read();m.read();read(a);read(b);read(c);read(d);
    
    m.dec();
    if(a==1){z=m;z.mul(b);p=1;q=z.div(mod);}
    else
    {
        x=pow(a,m.div(mod-1)+mod-1,mod);//a^(m-1)
        p=x;q=((x-1)*pow(a-1,mod-2,mod)%mod*b%mod+mod)%mod;
    }
    
    n.dec();
    a=c*p%mod;b=(c*q%mod+d)%mod;
    if(a==1){z=n;z.mul(b);P=1;Q=z.div(mod);}
    else
    {
        x=pow(a,n.div(mod-1)+mod-1,mod);
        P=x;Q=((x-1)*pow(a-1,mod-2,mod)%mod*b%mod+mod)%mod;
    }
    
    cout<<(((p*(P+Q)%mod)%mod+q)%mod+mod)%mod<<endl;
    
    scanf("\n");
    return 0;
}
