//DP+优化（非完美）
//最坏时间复杂度O(n^2),不过十分实用
var n,i,j,last:longint;
    x,p,c:array[1..1000000] of longint;
    f,sp:array[0..1000000] of int64;
begin
assign(input,'storage.in');
assign(output,'storage.out');
reset(input);rewrite(output);

readln(n);
for i:=1 to n do readln(x[i],p[i],c[i]);
sp[0]:=0;for i:=1 to n do sp[i]:=sp[i-1]+p[i];

f[0]:=0;last:=0;
for i:=1 to n do
begin
f[i]:=1 shl 62-1+1 shl 62;
for j:=last to i-1 do
begin
f[j]:=f[j]+(sp[i-1]-sp[j])*(x[i]-x[i-1]);
if f[j]<f[i] then begin f[i]:=f[j];last:=j;end;
end;
f[i]:=f[i]+c[i];
end;
writeln(f[n]);
close(input);close(output);
end.
