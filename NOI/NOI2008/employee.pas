//·ÑÓÃÁ÷
const oo=maxlongint*maxlongint;
var n,m,i,j,p,x,s,t:longint;vv,tmp,ans:int64;
    e,b:array[-15000..15000] of longint;
    w,c:array[-15000..15000] of int64;
    first,last:array[0..1200] of longint;
    dis,f:array[0..1200] of int64;
    o,v:array[0..1200] of boolean;
procedure add(x,y:longint;z,q:int64);
begin
//writeln(x,' ',y,' ',z,' ',q);
p:=p+1;
e[p]:=y;c[p]:=z;w[p]:=q;
if first[x]=0 then first[x]:=p else b[last[x]]:=p;last[x]:=p;
e[-p]:=x;c[-p]:=0;w[-p]:=-q;
if first[y]=0 then first[y]:=-p else b[last[y]]:=-p;last[y]:=-p;
end;
function min(a,b:int64):int64;
begin
if a<b then exit(a) else exit(b);
end;
function zkw(i:longint;flow:int64):int64;
var k:longint;r,d,l:int64;
begin
if i=n+2 then begin ans:=ans+dis[i]*flow;exit(flow);end;
k:=first[i];
o[i]:=true;
v[i]:=true;
r:=flow;
while k<>0 do
begin
  if c[k]>0 then
  begin
    l:=dis[i]+w[k]-dis[e[k]];
    if l<f[e[k]] then f[e[k]]:=l;
    if (l=0)and(not o[e[k]]) then
    begin
      d:=zkw(e[k],min(r,c[k]));
      r:=r-d;
      c[k]:=c[k]-d;c[-k]:=c[-k]+d;
      //writeln(i,' ',e[k],' ',d);
      if r=0 then break;
    end;
 end;
k:=b[k];
end;
o[i]:=false;
exit(flow-r);
end;


begin
assign(input,'employee.in');
assign(output,'employee.out');
reset(input);rewrite(output);

readln(n,m);
p:=0;
fillchar(b,sizeof(b),0);
fillchar(first,sizeof(first),0);
for i:=2 to n+1 do add(i,i-1,oo,0);
for i:=1 to n do
begin
read(x);
add(0,i,x,0);
add(i+1,n+2,x,0);
end;
readln;
for i:=1 to m do
begin
readln(s,t,vv);
add(s,t+1,oo,vv);
end;

fillchar(o,sizeof(o),false);
fillchar(dis,sizeof(dis),0);
ans:=0;
repeat
for i:=0 to n+2 do begin f[i]:=oo;v[i]:=false;end;
zkw(0,oo);
tmp:=oo;
for i:=0 to n+2 do if (not v[i])and(f[i]<tmp) then tmp:=f[i];
if tmp=oo then break;
for i:=0 to n+2 do if not v[i] then dis[i]:=dis[i]+tmp;
until false;
writeln(ans);
close(input);close(output);
end.





