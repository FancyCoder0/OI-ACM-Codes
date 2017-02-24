//两点间最大流优化
{
/************************************************************** 
    Problem: 2229
    User: slzxrly 
    Language: Pascal 
    Result: Accepted 
    Time:3600 ms 
    Memory:516 kb 
****************************************************************/ 
}
type arr=set of 1..150; 
var t,n,m,i,j,k,l,p,q,x,y,z,ss,tt,dd,ssss,ans:longint;ms:arr; 
    e,b,c,cc:array[-6000..6000] of longint; 
    first,last,h,vh:array[0..150] of longint; 
    minc:array[1..150,1..150] of longint; 
    s:array[1..300] of arr; 
    tt1,tt2:array[0..150] of longint; 
procedure add(x,y,z:longint); 
begin
p:=p+1; 
e[p]:=y;cc[p]:=z; 
if first[x]=0 then first[x]:=p else b[last[x]]:=p;last[x]:=p; 
e[-p]:=x;cc[-p]:=0; 
if first[y]=0 then first[y]:=-p else b[last[y]]:=-p;last[y]:=-p; 
end; 
function ISAP(i,flow:longint):longint; 
var k,r,d,minh:longint; 
begin
if i=tt then exit(flow); 
k:=first[i]; 
r:=flow; 
minh:=dd; 
while k<>0 do
begin
  if c[k]>0 then
  begin
    if h[i]=h[e[k]]+1 then
    begin
      if r<c[k] then d:=ISAP(e[k],r) 
                else d:=ISAP(e[k],c[k]); 
      c[k]:=c[k]-d;c[-k]:=c[-k]+d; 
      r:=r-d; 
      if h[ss]>=dd then exit(flow-r); 
      if r=0 then break; 
    end; 
  if h[e[k]]+1<minh then minh:=h[e[k]]+1; 
  end; 
k:=b[k]; 
end; 
  
if r=flow then
begin
dec(vh[h[i]]); 
if vh[h[i]]=0 then h[ss]:=dd; 
h[i]:=minh; 
inc(vh[h[i]]); 
end; 
exit(flow-r); 
end; 
procedure DFSs(i,f:longint); 
var k:longint; 
begin
s[f]:=s[f]+[i]; 
k:=first[i]; 
while k<>0 do
begin
  if c[k]>0 then
  if not (e[k] in s[f]) then DFSs(e[k],f); 
k:=b[k]; 
end; 
end; 
  
procedure work(v:longint); 
var i,j,x,y,flow:longint; 
begin
  x:=0;y:=0; 
  for i:=1 to n do
  if i in s[v] then
  if x=0 then x:=i 
         else
  if y=0 then begin y:=i;break;end; 
  if (x=0)or(y=0) then exit; 
  ss:=x; 
  tt:=y; 
  dd:=n; 
  c:=cc; 
  fillchar(h,sizeof(h),0); 
  fillchar(vh,sizeof(vh),0); 
  vh[0]:=n; 
  flow:=0; 
  while h[ss]<dd do flow:=flow+ISAP(ss,maxlongint); 
  
  ssss:=ssss+1;x:=ssss; 
  s[ssss]:=[]; 
  DFSs(ss,ssss); 
  ssss:=ssss+1;s[ssss]:=ms-s[x];y:=ssss; 
  tt1[0]:=0; 
  for i:=1 to n do
  if i in s[x] then begin inc(tt1[0]);tt1[tt1[0]]:=i;end; 
  tt2[0]:=0; 
  for i:=1 to n do
  if i in s[y] then begin inc(tt2[0]);tt2[tt2[0]]:=i;end; 
  
  for i:=1 to tt1[0] do
  for j:=1 to tt2[0] do
  begin
  if flow<minc[tt1[i],tt2[j]] then minc[tt1[i],tt2[j]]:=flow; 
  if flow<minc[tt2[j],tt1[i]] then minc[tt2[j],tt1[i]]:=flow; 
  end; 
  s[x]:=s[x]*s[v]; 
  s[y]:=s[v]-s[x]; 
  work(x); 
  work(y); 
end; 
  
begin
assign(input,'mincut.in');
assign(output,'mincut.out');
reset(input);rewrite(output);

readln(t); 
for l:=1 to t do
begin
  readln(n,m); 
  fillchar(first,sizeof(first),0); 
  fillchar(e,sizeof(e),0); 
  fillchar(b,sizeof(b),0); 
  fillchar(c,sizeof(c),0); 
  fillchar(cc,sizeof(cc),0); 
  fillchar(last,sizeof(last),0); 
  filldword(minc,sizeof(minc) div 4,maxlongint); 
  p:=0; 
  for i:=1 to m do
  begin
    readln(x,y,z); 
   add(x,y,z); 
    add(y,x,z); 
  end; 
  ms:=[]; 
  for i:=1 to n do ms:=ms+[i]; 
  ssss:=1; 
  s[1]:=ms; 
  work(1); 
  readln(q); 
  for k:=1 to q do
  begin
  readln(x); 
  ans:=0; 
  for i:=1 to n do
  for j:=i+1 to n do
  if minc[i,j]<=x then begin {writeln(i,' ',j);}ans:=ans+1;end; 
  writeln(ans); 
  end; 
  writeln; 
end;
close(input);close(output);
end.