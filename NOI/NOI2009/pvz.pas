//网络流 （有依赖的收益和费用问题，最小割）
//注意判断环等情况
var n,m,i,j,k,l,p,tt,zz,dd,ans,xx,yy:longint;pd:boolean;
    a:array[0..30,0..30] of longint;
    b,bb:array[0..30,0..30] of longint;
    cc:array[0..30,0..30,1..1000,1..2] of longint;
    cc2:array[0..30,0..30,1..1000,1..2] of longint;
    e,next,c:array[-1000000..1000000] of longint;
    first,last,h,vh:array[0..1000] of longint;
    v,no:array[0..30,0..30] of boolean;
    path:array[0..1000,1..2] of longint;
function min(a,b:longint):longint;
begin
if a<b then exit(a) else exit(b);
end;
procedure add(x,y,z:longint);
begin
//writeln(x,' ',y,' ',z);
p:=p+1;
e[p]:=y;c[p]:=z;
if first[x]=0 then first[x]:=p else next[last[x]]:=p;last[x]:=p;
e[-p]:=x;c[-p]:=0;
if first[y]=0 then first[y]:=-p else next[last[y]]:=-p;last[y]:=-p;
end;

function ISAP(i,flow:longint):longint;
var r,d,k,minh:longint;
begin
if i=n*m+1 then exit(flow);
minh:=dd;r:=flow;
k:=first[i];
while k<>0 do
begin
if c[k]>0 then
begin
  if h[i]=h[e[k]]+1 then
  begin
  d:=ISAP(e[k],min(r,c[k]));
  c[k]:=c[k]-d;c[-k]:=c[-k]+d;
  r:=r-d;
  if r=0 then break;
  end;
  minh:=min(minh,h[e[k]]+1);
end;
k:=next[k];
end;

if r=flow then
begin
dec(vh[h[i]]);
if vh[h[i]]=0 then h[0]:=dd;
h[i]:=minh;
inc(vh[h[i]]);
end;
exit(flow-r);
end;

procedure dfs(i,j:longint);
var k:longint;
begin
if (v[i,j])and(i=xx)and(j=yy) then begin pd:=true;exit;end;
v[i,j]:=true;
for k:=1 to b[i,j] do
if ((cc[i,j,k,1]=xx)and(cc[i,j,k,2]=yy))or(not v[cc[i,j,k,1],cc[i,j,k,2]]) then
dfs(cc[i,j,k,1],cc[i,j,k,2]);
for k:=j-1 downto 0 do
if ((i=xx)and(k=yy))or  (not v[i,k]) then
dfs(i,k);
inc(path[0,1]);
path[path[0,1],1]:=i;
path[path[0,1],2]:=j;
end;



begin
assign(input,'pvz.in');
assign(output,'pvz.out');
reset(input);rewrite(output);

readln(n,m);
for i:=0 to n-1 do
for j:=0 to m-1 do
begin
read(a[i,j],b[i,j]);
for k:=1 to b[i,j] do
begin
read(cc[i,j,k,1],cc[i,j,k,2]);
inc(bb[cc[i,j,k,1],cc[i,j,k,2]]);
cc2[cc[i,j,k,1],cc[i,j,k,2],bb[cc[i,j,k,1],cc[i,j,k,2]],1]:=i;
cc2[cc[i,j,k,1],cc[i,j,k,2],bb[cc[i,j,k,1],cc[i,j,k,2]],2]:=j;
end;
readln;
end;

fillchar(no,sizeof(no),true);
for i:=0 to n-1 do
for j:=0 to m-1 do
begin
pd:=false;
path[0,1]:=0;
fillchar(v,sizeof(v),false);
xx:=i;yy:=j;DFS(i,j);
if pd then
for k:=1 to path[0,1] do no[path[k,1],path[k,2]]:=false;
end;

ans:=0;
p:=0;
for i:=0 to n-1 do
for j:=0 to m-1 do
if no[i,j] then
begin
if a[i,j]>0 then begin add(0,i*m+j+1,a[i,j]);ans:=ans+a[i,j];end
            else add(i*m+j+1,n*m+1,-a[i,j]);
for k:=1 to bb[i,j] do
if no[cc2[i,j,k,1],cc2[i,j,k,2]] then add(i*m+j+1,cc2[i,j,k,1]*m+cc2[i,j,k,2]+1,maxlongint);
for k:=j+1 to m-1 do
if no[i,k] then add(i*m+j+1,i*m+k+1,maxlongint);
end;

dd:=n*m+2;
fillchar(h,sizeof(h),0);
fillchar(vh,sizeof(vh),0);
vh[0]:=dd;
while h[0]<dd do ans:=ans-ISAP(0,maxlongint);
writeln(ans);

close(input);close(output);
end.
