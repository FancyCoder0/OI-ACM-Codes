#include<cstdio> 
#include<cstring> 
#include<algorithm> 
//#include<iostream>  
//#include<set> 
//#include<map> 
//#include<iomanip> 
using namespace std; 
typedef long long int64; 
#define MAX(x,y) ((x)>(y)?(x):(y)) 
#define MIN(x,y) ((x)<(y)?(x):(y)) 
#define rep(i,x,y) for(i=x;i<=y;i++) 
#define rep_(i,x,y) for(i=x;i>=y;i--) 
  
const int MAXN=1010; 
int a[MAXN][MAXN]; 
int n,m,i,j,k,l,p,ans;bool pd; 
int main() 
{ 
    freopen("rec.in","r",stdin);
    freopen("rec.out","w",stdout);
    scanf("%d%d",&n,&m); 
    rep(i,1,n) 
    rep(j,1,m) 
    scanf("%d",&a[i][j]); 
      
    //ÆæÊý 
    rep(i,1,n) 
    rep(j,1,m) 
    { 
        rep(k,1,MIN(MIN(i,j),MIN(n-i+1,m-j+1))) 
        { 
            pd=1; 
            rep(l,j-k+1,j+k-1) 
            if(a[i-k+1][l]!=a[i+k-1][l]){pd=0;break;} 
            if(!pd)break; 
            rep(l,i-k+1,i+k-1) 
            if(a[l][j-k+1]!=a[l][j+k-1]){pd=0;break;} 
            if(!pd)break; 
            rep(l,1,k) 
            if(a[i-k+1][j-l+1]!=a[i-k+1][j+l-1]){pd=0;break;} 
            if(!pd)break; 
            rep(l,1,k) 
            if(a[i-l+1][j-k+1]!=a[i+l-1][j+k-1]){pd=0;break;} 
            if(!pd)break; 
        } 
        ans+=k-1; 
    }  
    rep(i,1,n-1) 
    rep(j,1,m-1) 
    { 
        rep(k,1,MIN(MIN(i,j),MIN(n-i,m-j))) 
        { 
            pd=1; 
            rep(l,j-k+1,j+k) 
            if(a[i-k+1][l]!=a[i+k][l]){pd=0;break;} 
            if(!pd)break; 
            rep(l,i-k+1,i+k) 
            if(a[l][j-k+1]!=a[l][j+k]){pd=0;break;} 
            if(!pd)break; 
            rep(l,1,k) 
            if(a[i-k+1][j-l+1]!=a[i-k+1][j+l]){pd=0;break;} 
            if(!pd)break; 
            rep(l,1,k) 
            if(a[i-l+1][j-k+1]!=a[i+l][j-k+1]){pd=0;break;} 
            if(!pd)break; 
        } 
        ans+=k-1; 
    } 
      
      
    printf("%d\n",ans); 
      
      
    scanf("\n"); 
    return 0; 
}
