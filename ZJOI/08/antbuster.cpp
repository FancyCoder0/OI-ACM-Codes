/*
    Problem:
    Algorithm:
    Note:
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
#define rep(i,x,y) for(i=x;i<=y;i++)
#define CL(S,x) memset(S,x,sizeof(S))
#define CP(S1,S2) memcpy(S1,S2,sizeof(S2))
#define sqr(x) ((x)*(x))
#define mp make_pair
typedef double real;

const int fx[4]={0,1,0,-1};
const int fy[4]={1,0,-1,0};
const int inf=1000000000;
struct node{int x,y;};
node operator-(node a,node b){return (node){a.x-b.x,a.y-b.y};}
int operator*(node a,node b){return a.x*b.y-b.x*a.y;}
int sqrdist(node a,node b){return sqr(a.x-b.x)+sqr(a.y-b.y);}
real dist(node a,node b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}

struct ant{node d;int age,level,hp,lastx,lasty;bool tar;};

int T,totT,n,m,cas,cad,car,infor[10][10],i,j;bool gameover=0,havecake=1;
int totant,dir,newx,newy,maxinfor,midist,last[10][10];
real po;int hps[200010];
node ca[25];
vector<ant> a,newa;
vector<ant>::iterator ant0,goal,nextant;
bool have[10][10];bool candir[4],yesdir[4];
ant newant;

bool inmap(int x,int y){return x>=0&&x<=n&&y>=0&&y<=m;}
bool jiao(node d1,node d2,node cd)
{
    real mind=inf,K,B,X,K2,B2;bool pd;
    
    if(d1.x==d2.x)pd=(cd.y>=min(d1.y,d2.y)&&cd.y<=max(d1.y,d2.y));
    else if(d1.y==d2.y)pd=(cd.x>=min(d1.x,d2.x)&&cd.x<=max(d1.x,d2.x));
    else
    {
        K=real(d2.y-d1.y)/(d2.x-d1.x);B=d1.y-K*d1.x;
        K2=-1/K;B2=cd.y-K2*cd.x;
        X=(B2-B)/(K-K2);
        pd=(X>=min(d1.x,d2.x)&&X<=max(d1.x,d2.x));
    }
    if(pd)mind=min(mind,abs((d1-cd)*(d2-cd))/dist(d1,d2));
    mind=min(mind,dist(cd,d1));
    mind=min(mind,dist(cd,d2));
    return (mind<=0.5);
}
bool hole_have_no_ant()
{
    for(ant0=a.begin();ant0!=a.end();ant0++)
    if((*ant0).d.x==0&&(*ant0).d.y==0)return 0;
    return 1;
}
int main()
{
    freopen("antbuster.in","r",stdin);
    freopen("antbuster.out","w",stdout);
    scanf("%d%d",&n,&m);
    scanf("%d%d%d",&cas,&cad,&car);
    rep(i,1,cas)scanf("%d%d",&ca[i].x,&ca[i].y);
    scanf("%d",&totT);
    
    for(po=1.1,i=1;i<=totT;i++,po=po*1.1)hps[i]=int(4*po);
    CL(last,127);
    
    rep(T,1,totT)
    {
        //出现新蚂蚁 
        if(a.size()<6&&hole_have_no_ant())
        {
            ++totant;
            newant.level=(totant-1)/6+1;
            newant.age=0;newant.hp=hps[newant.level];
            newant.d=(node){0,0};
            newant.tar=0;
            newant.lastx=newant.lasty=-1;
            a.push_back(newant);
        }
        
        
        //更新infor 
        for(ant0=a.begin();ant0!=a.end();ant0++)
        infor[(*ant0).d.x][(*ant0).d.y]+=((*ant0).tar)?5:2;
        
        //移动 
        CL(have,0);
        for(ant0=a.begin();ant0!=a.end();ant0++)
        have[(*ant0).d.x][(*ant0).d.y]=1;
        rep(i,1,cas)have[ca[i].x][ca[i].y]=1;
        
        for(ant0=a.begin();ant0!=a.end();ant0++)
        {
            CL(candir,0);CL(yesdir,0);maxinfor=-inf;
            bool canmove=0;
            rep(dir,0,3)
            {
                newx=(*ant0).d.x+fx[dir];
                newy=(*ant0).d.y+fy[dir];
                if(inmap(newx,newy)&&!have[newx][newy]&&mp(newx,newy)!=mp((*ant0).lastx,(*ant0).lasty))
                canmove=1,candir[dir]=yesdir[dir]=1,maxinfor=max(maxinfor,infor[newx][newy]);
            }
            (*ant0).lastx=(*ant0).d.x;
            (*ant0).lasty=(*ant0).d.y;
            if(canmove)
            {
                rep(dir,0,3)if(candir[dir])
                {
                    newx=(*ant0).d.x+fx[dir];
                    newy=(*ant0).d.y+fy[dir];
                    if(infor[newx][newy]<maxinfor)yesdir[dir]=0;
                }
                
                rep(dir,0,3)if(yesdir[dir])break;
                
                if(((*ant0).age+1)%5==0)
                for(dir=(dir+3)%4;!candir[dir];dir=(dir+3)%4);
                
                have[(*ant0).d.x][(*ant0).d.y]=0;
                (*ant0).d.x=(*ant0).d.x+fx[dir];
                (*ant0).d.y=(*ant0).d.y+fy[dir];
                have[(*ant0).d.x][(*ant0).d.y]=1;
            }
        }
        
        
        //拿cake 
        if(havecake)
        {
            for(ant0=a.begin();ant0!=a.end();ant0++)
            if((*ant0).d.x==n&&(*ant0).d.y==m)
            havecake=0,(*ant0).hp=min((*ant0).hp+hps[(*ant0).level]/2,hps[(*ant0).level]),
            (*ant0).tar=1;
            
        }
        
        
        //塔攻击 
        rep(i,1,cas)
        {
            midist=inf;
            for(ant0=a.begin();ant0!=a.end();ant0++)
            if(sqrdist((*ant0).d,ca[i])<=car*car)
            if((*ant0).tar){goal=ant0;midist=sqrdist((*ant0).d,ca[i]);break;}
            else if(sqrdist((*ant0).d,ca[i])<midist)goal=ant0,midist=sqrdist((*ant0).d,ca[i]);
            if(midist<inf)
            {
                for(ant0=a.begin();ant0!=a.end();ant0++)
                if(jiao(ca[i],(*goal).d,(*ant0).d))(*ant0).hp-=cad;
            }
        }
        
        newa.clear();
        for(ant0=a.begin();ant0!=a.end();ant0++)//hui yuejie?
        if((*ant0).hp<0){if((*ant0).tar)havecake=1;}
        else newa.push_back(*ant0);
        a=newa;
        
        for(ant0=a.begin();ant0!=a.end();ant0++)
        if((*ant0).tar&&(*ant0).d.x==0&&(*ant0).d.y==0)gameover=1;
        if(gameover)break;
        
        rep(i,0,n)rep(j,0,m)infor[i][j]=max(infor[i][j]-1,0);
        for(ant0=a.begin();ant0!=a.end();ant0++)(*ant0).age++;
    }
    if(gameover)printf("Game over after %d seconds\n",T);
    else printf("The game is going on\n");
    
    printf("%d\n",a.size());
    for(ant0=a.begin();ant0!=a.end();ant0++)
    printf("%d %d %d %d %d\n",(*ant0).age,(*ant0).level,(*ant0).hp,(*ant0).d.x,(*ant0).d.y);
       
    
    scanf("\n");
    return 0;
}
