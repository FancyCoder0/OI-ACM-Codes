/*
    Problem:
    Algorithm:
        ö��������Щ�����м�һ������ͨ�����������
        ��ô���̸���˲���ɵļ��飬
        ��������������µĴ𰸣��ݳ⼴�ɡ�
        ��֤�������Ĵ�ʱ����G[i]Ϊǰi�ж������Ĵ�
        G[0]=-1,G[i]=-sigma(G[j]*last(j+1..i))
        last(i,j)��ʾi..j��Щ���ﱣ֤һЩ�зָ������ŵķ���
        =��ɼ���������Ƶķ�����״ѹdpԤ�����ɣ�
    Note:
        O(N^5*2^N)
*/
#include<cstdio>
#include<cstring>
using namespace std;
#define rep(i,x,y) for(i=x;i<=y;i++)
#define CL(S,x) memset(S,x,sizeof(S))

const int MAXN=16;
const int MAXS=1<<15;
const int mod=19901013;
int n,m,i,j,x,L,R,U,D,S,lim,st[MAXN],g,ans,tot;
bool a[MAXN][MAXN];
int sum[MAXN][MAXN][MAXN][MAXN],G[MAXN];
int f[MAXN+1][MAXN][MAXS],*f0,*f1;

char read(){char x;for(x=getchar();x<=32;x=getchar());return x;}

#define add(a,b) a=((a)+(b))%mod
#define mul(a,b) a=((a)*((b)%mod)%mod)
int main()
{
    freopen("domino.in","r",stdin);
    freopen("domino.out","w",stdout);
    scanf("%d%d",&n,&m);
    rep(i,1,n)rep(j,1,m)a[i][j]=(read()=='.');
    
    rep(L,1,m)rep(R,L,m)rep(U,1,n)
    {
        lim=(1<<(R-L+1))-1;
        rep(S,0,lim)f[U][L][S]=0;f[U][L][0]=1;
        rep(i,U,n)
        {
            rep(j,L,R)
            {
                f0=f[i][j];if(j==R)f1=f[i+1][L];else f1=f[i][j+1];
                rep(S,0,lim)f1[S]=0;x=j-L;//��ǰ2���Ƶ�x+1λ 
                rep(S,0,lim)if(f0[S])
                {
                    add(f1[S&(~(1<<x))],f0[S]);
                    if(j>L&&a[i][j]&&a[i][j-1]&&(!(S>>(x-1)&1)))add(f1[S|(3<<(x-1))],f0[S]);
                    if(i>U&&a[i][j]&&a[i-1][j]&&(!(S>>x&1)))add(f1[S|(1<<x)],f0[S]);
                }
            }
            rep(S,0,lim)add(sum[U][i][L][R],f1[S]);
        }   
    }
    
    
    rep(S,0,(1<<(m-1))-1)
    {
        CL(G,0);G[0]=-1;
        g=0;rep(i,1,m-1)if(S>>(i-1)&1)st[++g]=i;st[++g]=m;
        rep(D,1,n)
        rep(U,0,D-1)
        {
            tot=1;rep(i,1,g)mul(tot,1LL*sum[U+1][D][st[i-1]+1][st[i]]);
            add(G[D],-1LL*tot*G[U]);
        }
        if(g&1)add(ans,G[D-1]);else add(ans,-G[D-1]);
    }
    printf("%d\n",add(ans,mod));
    scanf("\n");
    return 0;
}
