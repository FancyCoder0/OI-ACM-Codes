//颇难的树形DP DFS实现，常数较大
var n,i,j,p,x,root,leaf,num,no1,no2:longint;ans,total:int64;XZ:boolean;
    a,first,c,q:array[1..1000000] of longint;
    e,b:array[1..2000000] of longint;
    v:array[1..1000000] of boolean;
    f:array[1..1000000,0..1] of int64;
procedure add(x,y:longint);
begin
p:=p+1;
e[p]:=y;if first[x]=0 then first[x]:=p else b[c[x]]:=p;c[x]:=p;
p:=p+1;
e[p]:=x;if first[y]=0 then first[y]:=p else b[c[y]]:=p;c[y]:=p;
end;

procedure DFS(i,fa:longint);
var k:longint;
begin
v[i]:=true; inc(num);q[num]:=i;
k:=first[i];
while k<>0 do
begin
if k<>fa then if v[e[k]] then begin root:=e[k];leaf:=i;if no1=0 then no1:=k else no2:=k;end
                         else if odd(k) then DFS(e[k],k+1) else DFS(e[k],k-1);
k:=b[k];
end;
end;

procedure get(i,j,fa:longint);
var k:longint;
begin
if f[i,j]<>-1 then exit;

if j=0 then
begin
f[i,j]:=0;
k:=first[i];
while k<>0 do
begin
if k<>fa then
if (k<>no1) and (k<>no2) then
begin
if odd(k) then get(e[k],0,k+1) else get(e[k],0,k-1);
if odd(k) then get(e[k],1,k+1) else get(e[k],1,k-1);
if f[e[k],0]>f[e[k],1] then f[i,j]:=f[i,j]+f[e[k],0] else f[i,j]:=f[i,j]+f[e[k],1];
end;
k:=b[k];
end;
end
else
begin
if (i=leaf) and (XZ) then f[i,j]:=0 else f[i,j]:=a[i];
k:=first[i];
while k<>0 do
begin
if k<>fa then
if (k<>no1) and (k<>no2) then
begin
if odd(k) then get(e[k],0,k+1) else get(e[k],0,k-1);
f[i,j]:=f[i,j]+f[e[k],0];
end;
k:=b[k];
end;
end;
end;


begin
assign(input,'knight.in');
assign(output,'knight.out');
reset(input);rewrite(output);

readln(n);
p:=0;
for i:=1 to n do
begin
readln(a[i],x);
add(i,x);
end;
fillchar(v,sizeof(v),false);
ans:=0;
for i:=1 to n do
if not v[i] then
begin
num:=0;no1:=0;DFS(i,0);

XZ:=false;
for j:=1 to num do begin f[q[j],0]:=-1;f[q[j],1]:=-1;end;
get(root,0,0);total:=f[root,0];

XZ:=true;
for j:=1 to num do begin f[q[j],0]:=-1;f[q[j],1]:=-1;end;
get(root,0,0);
get(root,1,0);
if f[root,0]>total then total:=f[root,0];
if f[root,1]>total then total:=f[root,1];

ans:=ans+total;
end;

writeln(ans);
close(input);close(output);
end.

