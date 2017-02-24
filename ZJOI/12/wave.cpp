#include<iostream>
#include<cstring>
#include<iomanip>
#define rep(i,x,y) for(i=x;i<=y;i++)
#define CL(S,x) memset(S,x,sizeof(S))
#define CP(S1,S2) memcpy(S1,S2,sizeof(S2))
using namespace std;
 
typedef long double ld;
int n,m,w,i,j,k,l,d,p,sum;
__float128 f[101][10010][3],f2[101][10010][3],t,res,ans;
int a[200];
int main()
{
    cin>>n>>m>>w;
    d=n*n/2+1;
     
    f[1][-2+d][0]=1;
    f[1][-1+d][1]=2;
    f[1][0+d][2]=1;
    sum=2;
    rep(i,2,n)
    {
        rep(k,1,min(i,n-i+1)*2)rep(j,-sum,sum)rep(l,0,2){f2[k][j+d][l]=f[k][j+d][l];f[k][j+d][l]=0;}
         
        rep(k,1,min(i,n-i+1)*2)
        rep(j,-sum,sum)
        {
            t=f2[k][j+d][0];
            if(t>0)
            {
                f[k][j+d][0]+=t*(2*k);
                f[k-1][j+2*i+d][0]+=t*(k-1);
                f[k+1][j-2*i+d][0]+=t*(k+1);
                f[k+1][j-i+d][1]+=t*2;
                f[k][j+i+d][1]+=t*2;
            }
            t=f2[k][j+d][1];
            if(t>0)
            {
                f[k][j+d][1]+=t*(2*k-1);
                f[k-1][j+2*i+d][1]+=t*(k-1);
                f[k+1][j-2*i+d][1]+=t*k;
                f[k+1][j-i+d][2]+=t;
                f[k][j+i+d][2]+=t;
            }
            t=f2[k][j+d][2];
            if(t>0)
            {
                f[k][j+d][2]+=t*(2*k-2);
                f[k-1][j+2*i+d][2]+=t*(k-1);
                f[k+1][j-2*i+d][2]+=t*(k-1);
            }
        }
         
        sum=min(sum+2*i,d);
    }
     
    rep(j,m,d)res+=f[1][j+d][2];
    ans=1;rep(i,1,n)ans=ans*i;
    ans=res/ans;
     
    while(w--){ans*=10;p=int(ans);ans-=p;a[++a[0]]=p;}
    ans*=10;p=int(ans);if(p>=5)a[a[0]]++;
    cout<<"0.";rep(i,1,a[0])cout<<a[i];cout<<endl;
     
    return 0;
}
