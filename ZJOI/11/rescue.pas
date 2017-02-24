//经典题 用K条路径覆盖整个图 拆点
//有下界的网络流可以在下界的边上费用变为-∞，之后再加上
//SPFA流
//建图：源点S 汇点T
//S--起点，K，0
//每个点A：A+n（拆点）--A，1，-∞  (为了经过每个点，强行要走）
                  A--T,1,0
//每条边（A-B)：A--B+n,1,费用
var n,m,kk,i,j,k,l,p,x,y,z,x1,x2,x3,ans,total:longint;
    a:array[0..151,1..151,1..151] of longint;
    tt:array[1..151,1..151] of longint;
    e,b,c,w:array[-50000..50000] of longint;
    first,last:array[1..310] of longint;
    dis,v:array[1..310] of longint;
    f,path,fa:array[1..100000] of longint;
function min(a,b:longint):longint;
begin
if a<b then exit(a) else exit(b);
end;
function max(a,b:longint):longint;
begin
if a>b then exit(a) else exit(b);
end;
procedure add(x,y,z,q:longint);
begin
p:=p+1;
e[p]:=y;c[p]:=z;w[p]:=q;
if first[x]=0 then first[x]:=p else b[last[x]]:=p;last[x]:=p;
e[-p]:=x;c[-p]:=0;w[-p]:=-q;
if first[y]=0 then first[y]:=-p else b[last[y]]:=-p;last[y]:=-p;
end;
function SPFA:longint;
var i,j,k,l,p,d,flow:longint;
begin
filldword(dis,sizeof(dis) div 4,maxlongint);
fillchar(v,sizeof(v),0);
i:=1;j:=1;f[1]:=1+n;dis[1+n]:=0;p:=0;path[1]:=0;
repeat
  k:=first[f[i]];
  while k<>0 do
     begin
     if c[k]>0 then
     if dis[f[i]]+w[k]<dis[e[k]] then
       begin
       dis[e[k]]:=dis[f[i]]+w[k];
       if v[e[k]]<>0 then begin fa[v[e[k]]]:=i;path[v[e[k]]]:=k;end
                            else
       begin
       j:=j+1;
       v[e[k]]:=j;
       f[j]:=e[k];
       fa[j]:=i;
       path[j]:=k;
       end;
       end;
    k:=b[k];
    end;

if f[i]=2*n+1 then p:=i;
v[f[i]]:=0;
i:=i+1;
until i>j;
if dis[2*n+1]=maxlongint then exit(maxlongint);
flow:=maxlongint;
i:=p;
while path[i]<>0 do
begin
flow:=min(flow,c[path[i]]);
i:=fa[i];
end;

i:=p;
while path[i]<>0 do
begin
c[path[i]]:=c[path[i]]-flow;
c[-path[i]]:=c[-path[i]]+flow;
i:=fa[i];
end;

exit(dis[2*n+1]);
end;


begin
assign(input,'rescue.in');
assign(output,'rescue.out');
reset(input);rewrite(output);

readln(n,m,kk);
n:=n+1;
filldword(tt,sizeof(tt) div 4,maxlongint div 2);
for i:=1 to m do
begin
readln(x,y,z);
x:=x+1;y:=y+1;
if z<tt[x,y] then tt[x,y]:=z;
if z<tt[y,x] then tt[y,x]:=z;
end;
a[0]:=tt;
for k:=1 to n do
begin
a[k]:=a[k-1];
for i:=1 to n do
for j:=1 to n do
if (i<>k)and(j<>k)and(i<>j) then
if a[k-1,i,k]+a[k-1,k,j]<a[k,i,j] then a[k,i,j]:=a[k-1,i,k]+a[k-1,k,j];
end;
p:=0;
add(1+n,1,kk,0);
for i:=2 to n do add(i+n,i,1,-5000000);//////
for i:=1 to n do add(i,2*n+1,1,0);//////
for i:=1 to n do
for j:=i+1 to n do
add(i,j+n,1,a[max(i,j),i,j]);

ans:=(n-1)*5000000;
repeat
total:=SPFA;
if total=maxlongint then break;
ans:=ans+total;
until false;
writeln(ans);
close(input);close(output);
end.



