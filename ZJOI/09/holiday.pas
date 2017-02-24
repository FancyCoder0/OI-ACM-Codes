var tt,l,n,i,j,p,x,s,t,dd,people,ans:longint;
    e:array[-100000..100000] of longint;
    c:array[-100000..100000] of longint;
    b:array[-100000..100000] of longint;
    h,vh,first,cc:array[0..200] of longint;
    pd1,pd2:array[1..200] of longint;
    r:array[1..200,1..200] of longint;
procedure add(x,y,z:longint);
begin
     inc(p);
     e[p]:=y;e[-p]:=x;
     c[p]:=z;c[-p]:=0;
     if first[x]=0 then first[x]:=p else b[cc[x]]:=p;
     cc[x]:=p;
     if first[y]=0 then first[y]:=-p else b[cc[y]]:=-p;
     cc[y]:=-p;
end;
function min(a,b:longint):longint;
begin
if a<b then exit(a) else exit(b);
end;

function ISAP(i,flow:longint):longint;
var k,r,minh,d:longint;
begin
if i=t then exit(flow);
r:=flow;minh:=dd;
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
        if h[s]>=dd then exit(flow-r);
        if r=0 then break;
        end;
    minh:=min(minh,h[e[k]]);
    end;
k:=b[k];
end;
if r=flow then
  begin
  dec(vh[h[i]]);
  if vh[h[i]]=0 then h[s]:=dd;
  h[i]:=minh+1;
  inc(vh[h[i]]);
  end;
exit(flow-r);
end;

begin
assign(input,'holiday.in');
assign(output,'holiday.out');
reset(input);rewrite(output);

readln(tt);
for l:=1 to tt do
begin
readln(n);
p:=0;
fillchar(first,sizeof(first),0);
fillchar(b,sizeof(b),0);

for i:=1 to n do add(0,i,1);
for i:=n+1 to n+n do add(i,2*n+1,1);

for i:=1 to n do read(pd1[i]);readln;
for i:=1 to n do read(pd2[i]);readln;
for i:=1 to n do
begin
for j:=1 to n do
read(r[i,j]);
readln;
end;

people:=0;
for i:=1 to n do
if (pd1[i]=0) or ((pd1[i]=1)and(pd2[i]=0)) then
begin
inc(people);
for j:=1 to n do
if ((i=j)or(r[i,j]=1))and(pd1[j]=1) then add(i,n+j,1);
end;

ans:=0;s:=0;t:=2*n+1;dd:=2*n+2;
fillchar(h,sizeof(h),0);
fillchar(vh,sizeof(vh),0);
vh[0]:=dd;
while h[s]<dd do
ans:=ans+ISAP(s,maxlongint);

if ans=people then writeln(chr(94),chr(95),chr(94))
              else writeln(chr(84),chr(95),chr(84));
end;

close(input);close(output);
end.


