//平面最大正方形+宽度相同高度不同的平面最大矩形
//DP+单调队列 O(n^3) 理论这么低，常数还是写了这么大。。。
var p,q,r,i,j,k,l,max:longint;cc:char;
      a,b:array[1..150,1..150,1..150] of byte;
      c:array[1..150,1..150,1..150] of longint;
      d,w1,w2,h1,h2:array[1..150] of longint;
function min(a,b:longint):longint;
begin
if a<b then exit(a) else exit(b);
end;
procedure try(x:longint);
var i,j,k:longint;
begin
fillchar(w1,sizeof(w1),0);
j:=0;
for i:=1 to x do
begin
j:=j+1;w1[j]:=i;
while (j>1)and(d[w1[j]]<=d[w1[j-1]]) do begin w1[j-1]:=w1[j];j:=j-1;end;
if j=1 then h1[i]:=1
          else h1[i]:=w1[j-1]+1;
end;

fillchar(w1,sizeof(w1),0);
j:=0;
for i:=x downto 1 do
begin
j:=j+1;w1[j]:=i;
while (j>1)and(d[w1[j]]<=d[w1[j-1]]) do begin w1[j-1]:=w1[j];j:=j-1;end;
if j=1 then h2[i]:=x
          else h2[i]:=w1[j-1]-1;
end;
for i:=1 to x do if d[i]*(h2[i]-h1[i]+1)>max then max:=d[i]*(h2[i]-h1[i]+1);
end;

procedure work(aa,bb,cc:longint);
var i,j,k,l,p:longint;
begin
fillchar(c,sizeof(c),0);
for i:=1 to aa do
begin
for j:=1 to bb do
if b[i,j,1]=1 then c[i,j,1]:=1 else c[i,j,1]:=0;
for k:=1 to cc do
if b[i,1,k]=1 then c[i,1,k]:=1 else c[i,1,k]:=0;
for j:=2 to bb do
for k:=2 to cc do
if b[i,j,k]=0 then c[i,j,k]:=0
              else c[i,j,k]:=min(min(c[i,j-1,k-1],c[i,j-1,k]),c[i,j,k-1])+1;
end;
for j:=1 to bb do
for k:=1 to cc do
begin
for i:=1 to aa do d[i]:=c[i,j,k];try(aa);
end;
end;


begin
assign(input,'gift.in');
assign(output,'gift.out');
reset(input);rewrite(output);

readln(p,q,r);
for j:=1 to q do
for i:=1 to p do
begin
for k:=1 to r do
begin
read(cc);
if cc='P' then a[i,j,k]:=0 else a[i,j,k]:=1;
end;
readln;
end;

max:=0;
for i:=1 to p do
for j:=1 to q do
for k:=1 to r do
b[i,j,k]:=a[i,j,k];
work(p,q,r);

for i:=1 to p do
for j:=1 to q do
for k:=1 to r do
b[j,i,k]:=a[i,j,k];
work(q,p,r);

for i:=1 to p do
for j:=1 to q do
for k:=1 to r do
b[k,i,j]:=a[i,j,k];
work(r,p,q);

writeln(4*max);
close(input);close(output);
end.
