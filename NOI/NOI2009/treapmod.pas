//����DP
//F(i,j,k) i-jһ�����нڵ㶼Ҫ>=b[k]����ֵ
//O(n^4) ����С
var n,kk,i,j,k,t,l,p,dd:longint;pd:boolean;
    a,b,c:array[0..70] of longint;
    f:array[1..70,1..70,0..70] of longint;
    sum:array[0..70] of longint;
    //s:array[1..70,1..70,1..70] of longint;
function min(a,b:longint):longint;
begin
if a<b then exit(a) else exit(b);
end;
function get(i,j,k:longint):longint;
var t:longint;
begin
if i>j then exit(0);
if f[i,j,k]<>-1 then exit(f[i,j,k]);
get:=maxlongint;
for t:=i to j do
begin
if b[t]>=b[k] then get:=min(get,get(i,t-1,t)+get(t+1,j,t)+(sum[j]-sum[i-1]));  {�����䣬��Сֵ�ı�}
                   get:=min(get,get(i,t-1,k)+get(t+1,j,k)+(sum[j]-sum[i-1])+kk);  {���ı䣬��Сֵ����}
end;

f[i,j,k]:=get;
end;

begin
assign(input,'treapmod.in');
assign(output,'treapmod.out');
reset(input);rewrite(output);

readln(n,kk);
for i:=1 to n do read(a[i]);readln;
for i:=1 to n do read(b[i]);readln;
for i:=1 to n do read(c[i]);readln;
for i:=1 to n-1 do
for j:=i+1 to n do
if a[i]>a[j] then
begin
  t:=a[i];a[i]:=a[j];a[j]:=t;
  t:=b[i];b[i]:=b[j];b[j]:=t;
  t:=c[i];c[i]:=c[j];c[j]:=t;
end;
sum[0]:=0;for i:=1 to n do sum[i]:=sum[i-1]+c[i];

fillchar(f,sizeof(f),255);
b[0]:=-maxlongint;
writeln(get(1,n,0));

close(input);close(output);
end.
