//DP ÓÐÄÑ¶È
var n,m,k,i,j,a,b,ans:longint;
    f:array[0..151,0..151,0..21,0..21] of longint;
function max(a,b:longint):longint;
begin
if a>b then exit(a) else exit(b);
end;
begin
assign(input,'party.in');
assign(output,'party.out');
reset(input);rewrite(output);
readln(n,m,k);
fillchar(f,sizeof(f),0);
f[0,0,0,0]:=1;
for i:=0 to n do
for j:=0 to m do
for a:=0 to k do
for b:=0 to k do
if f[i,j,a,b]<>0 then
begin
if a+1<=k then f[i+1,j,a+1,max(0,b-1)]:=(f[i+1,j,a+1,max(0,b-1)]+f[i,j,a,b]) mod 12345678;
if b+1<=k then f[i,j+1,max(0,a-1),b+1]:=(f[i,j+1,max(0,a-1),b+1]+f[i,j,a,b]) mod 12345678;
end;
ans:=0;
for i:=0 to k do
for j:=0 to k do
ans:=(ans+f[n,m,i,j]) mod 12345678;
writeln(ans);
close(input);close(output);
end.

