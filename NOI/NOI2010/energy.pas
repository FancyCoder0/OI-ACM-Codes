//ÈÝ³â£¨ÓÐÐ©²»¶®£©
//O(nlogn)
var i,j:longint;n,m,t,ans:int64;
    a:array[1..100000] of int64;
begin
readln(n,m);
if n>m then begin t:=n;n:=m;m:=t;end;
for i:=n downto 1 do
begin
a[i]:=(n div i)*(m div i);
for j:=2 to n div i do
a[i]:=a[i]-a[i*j];
end;

ans:=0;
for i:=1 to n do ans:=ans+a[i]*(2*i-1);
writeln(ans);
end.
