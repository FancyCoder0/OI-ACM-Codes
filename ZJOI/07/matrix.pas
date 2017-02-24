//¶þ·ÖÍ¼Æ¥Åä ISAP
var t,n,i,j,k,l,p,x,dd,ans:longint;
    e,b,s:array[-50000..50000] of longint;
    first,c,h,vh:array[0..500] of longint;
procedure add(x,y:longint);
begin
//writeln(x,' ',y);
p:=p+1;
e[p]:=y;s[p]:=1;
e[-p]:=x;s[-p]:=0;
if first[x]=0 then first[x]:=p else b[c[x]]:=p;c[x]:=p;
if first[y]=0 then first[y]:=-p else b[c[y]]:=-p;c[y]:=-p;
end;
function min(a,b:longint):longint;
begin
if a<b then exit(a) else exit(b);
end;
function ISAP(i,flow:longint):longint;
var r,d,minh,k:longint;
begin
if i=2*n+1 then exit(flow);
minh:=dd;r:=flow;
k:=first[i];
while k<>0 do
begin
if s[k]>0 then
begin
if h[i]=h[e[k]]+1 then
begin
d:=ISAP(e[k],min(r,s[k]));
s[k]:=s[k]-d;s[-k]:=s[-k]+d;
r:=r-d;
if h[0]>=dd then exit(flow-r);
if r=0 then break;
end;
minh:=min(minh,h[e[k]]);
end;
k:=b[k];
end;
if r=flow then
begin
dec(vh[h[i]]);
if vh[h[i]]=0 then h[0]:=dd;
h[i]:=minh+1;
inc(vh[h[i]]);
end;
exit(flow-r);
end;


begin
assign(input,'matrix.in');
assign(output,'matrix.out');
reset(input);rewrite(output);

readln(t);
for l:=1 to t do
begin

readln(n);
p:=0;
fillchar(e,sizeof(e),0);
fillchar(s,sizeof(s),0);
fillchar(b,sizeof(b),0);
fillchar(first,sizeof(first),0);
fillchar(c,sizeof(c),0);
for i:=1 to n do add(0,i);
for i:=n+1 to n*2 do add(i,2*n+1);

for i:=1 to n do
for j:=1 to n do
begin
read(x);
if x=1 then add(j,n+i);
end;
fillchar(h,sizeof(h),0);
fillchar(vh,sizeof(vh),0);
vh[0]:=2*n+2;ans:=0;dd:=2*n+2;
while h[0]<dd do
ans:=ans+ISAP(0,maxlongint);
if ans=n then writeln('Yes') else writeln('No');
end;
close(input);close(output);
end.
