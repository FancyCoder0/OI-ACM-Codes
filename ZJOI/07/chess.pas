//‘§¥¶¿Ì+DP
var n,m,i,j,k,p,ans1,ans2:longint;
    a,u,l,r:array[1..2000,1..2000] of longint;
    f:array[1..2000,1..2000] of longint;
function min(a,b,c:longint):longint;
begin
if (a<=b) and (a<=c) then exit(a)
                     else
if (b<=c) then exit(b)
          else exit(c);
end;
begin
assign(input,'chess.in');
assign(output,'chess.out');
reset(input);rewrite(output);

readln(n,m);
for i:=1 to n do
begin
for j:=1 to m do read(a[i,j]);readln;
end;

for i:=1 to m do u[1,i]:=1;
for i:=2 to n do
for j:=1 to m do
if a[i,j] xor a[i-1,j]=1 then u[i,j]:=u[i-1,j]+1 else u[i,j]:=1;

for i:=1 to n do l[i,1]:=1;
for i:=1 to n do
for j:=2 to m do
if a[i,j] xor a[i,j-1]=1 then l[i,j]:=l[i,j-1]+1 else l[i,j]:=1;

for i:=1 to n do r[i,m]:=1;
for i:=1 to n do
for j:=m-1 downto 1 do
if a[i,j] xor a[i,j+1]=1 then r[i,j]:=r[i,j+1]+1 else r[i,j]:=1;

for i:=1 to m do f[1,i]:=1;
for i:=1 to n do f[i,1]:=1;
if (n>0) or (m>0) then ans1:=1;
for i:=2 to n do
for j:=2 to m do
if (a[i,j]=a[i-1,j-1]) and (a[i,j] xor a[i-1,j]=1) and (a[i,j] xor a[i,j-1]=1) then
begin
f[i,j]:=min(f[i-1,j-1],f[i-1,j],f[i,j-1])+1;
if f[i,j]>ans1 then ans1:=f[i,j];
end
else f[i,j]:=1;
writeln(ans1*ans1);

ans2:=0;
for i:=1 to n do
for j:=1 to m do
begin
if (i>1) and (a[i,j] xor a[i-1,j]=1) then
begin
l[i,j]:=min(l[i,j],l[i-1,j],maxlongint);
r[i,j]:=min(r[i,j],r[i-1,j],maxlongint);
end;
if (l[i,j]+r[i,j]-1)*u[i,j]>ans2 then ans2:=(l[i,j]+r[i,j]-1)*u[i,j];
end;

writeln(ans2);
close(input);close(output);
end.







