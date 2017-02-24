//ISAP+SPFAÁ÷
const oo=maxlongint*maxlongint;
var n,m,k,i,p:longint;ans:int64;
    yy:array[1..5000,1..4] of int64;
    e:array[-20000..20000] of int64;
    c:array[-20000..20000] of int64;
    w:array[-20000..20000] of int64;
    b:array[-20000..20000] of int64;
    first,cc:array[0..1000] of int64;
    h,vh:array[0..1001] of longint;
    f,last,path:array[1..80000] of longint;
    v:array[0..1000] of longint;
    dis:array[0..1000] of int64;
procedure add(x,y,z,q:int64);
begin
inc(p);
e[p]:=y;e[-p]:=x;
c[p]:=z;c[-p]:=0;
w[p]:=q;w[-p]:=-q;
if first[x]=0 then first[x]:=p else b[cc[x]]:=p;cc[x]:=p;
if first[y]=0 then first[y]:=-p else b[cc[y]]:=-p;cc[y]:=-p;
end;
function min(a,b:int64):int64;
begin
if a<b then exit(a) else exit(b);
end;

function ISAP(i:longint;flow:int64):int64;
var k,minh:longint;r,d:int64;
begin
if i=n then exit(flow);
r:=flow;minh:=n;
k:=first[i];
while k<>0 do
begin
 if c[k]>0 then
  begin
   if h[i]=h[e[k]]+1 then
    begin
    d:=ISAP(e[k],min(r,c[k]));
    r:=r-d;
    c[k]:=c[k]-d;c[-k]:=c[-k]+d;
    if h[1]>=n then exit(flow-r);
    if r=0 then break;
    end;
  minh:=min(minh,h[e[k]]);
  end;
k:=b[k];
end;
if flow=r then
begin
dec(vh[h[i]]);
if vh[h[i]]=0 then h[1]:=n;
h[i]:=minh+1;
inc(vh[h[i]]);
end;
exit(flow-r);
end;

function SPFA(s,t:longint):int64;
var i,j,k,r:longint;flow:int64;
begin
for i:=0 to n do dis[i]:=oo;
fillchar(v,sizeof(v),0);
fillchar(last,sizeof(last),0);
fillchar(path,sizeof(path),0);
i:=1;j:=1;f[1]:=s;last[1]:=0;path[1]:=0;v[s]:=1;dis[s]:=0;
r:=0;
repeat
k:=first[f[i]];
while k<>0 do
 begin
  if c[k]>0 then
    if dis[f[i]]+w[k]<dis[e[k]] then
     begin
      dis[e[k]]:=dis[f[i]]+w[k];
      if v[e[k]]<>0 then begin last[v[e[k]]]:=i;path[v[e[k]]]:=k;end
                    else
                    begin
                    j:=j+1;
                    f[j]:=e[k];
                    last[j]:=i;
                    path[j]:=k;
                    v[e[k]]:=j;
                    end;
     end;
 k:=b[k];
 end;

if f[i]=t then r:=i;
v[f[i]]:=0;
i:=i+1;
until i>j;
if dis[t]=oo then exit(oo);

flow:=oo;
i:=r;
while last[i]<>0 do
begin
flow:=min(flow,c[path[i]]);
i:=last[i];
end;
i:=r;
while last[i]<>0 do
begin
c[path[i]]:=c[path[i]]-flow;
c[-path[i]]:=c[-path[i]]+flow;
i:=last[i];
end;
ans:=ans+dis[t]*flow;
exit(flow);
end;

begin
assign(input,'network.in');
assign(output,'network.out');
reset(input);rewrite(output);

readln(n,m,k);
for i:=1 to m do readln(yy[i,1],yy[i,2],yy[i,3],yy[i,4]);

p:=0;
fillchar(b,sizeof(b),0);
fillchar(first,sizeof(first),0);
for i:=1 to m do add(yy[i,1],yy[i,2],yy[i,3],0);
ans:=0;
fillchar(h,sizeof(h),0);
fillchar(vh,sizeof(vh),0);
vh[0]:=n;
while h[1]<n do ans:=ans+ISAP(1,oo);
write(ans,' ');

add(0,1,k,0);
for i:=1 to m do add(yy[i,1],yy[i,2],oo,yy[i,4]);
ans:=0;
repeat
until SPFA(0,n)=oo;
writeln(ans);

close(input);close(output);
end.
