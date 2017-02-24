//平面最小割转最短路(Dijkstra+Heap 比SPFA快好多)
var n,i,j,p,x,num:longint;
    e,b,w:array[1..2000000] of longint;
    first,c,wz:array[0..250001] of longint;
    h:array[1..250002] of record
                                                p,s:longint;
                                                end;
procedure add(x,y,z:longint);
begin
p:=p+1;
e[p]:=y;w[p]:=z;
if first[x]=0 then first[x]:=p else b[c[x]]:=p;c[x]:=p;
end;
procedure delmin;
var i,tt,tmp:longint;
begin
wz[h[1].p]:=0;
h[1].p:=h[num].p;
h[1].s:=h[num].s;
wz[h[1].p]:=1;
dec(num);
i:=1;
repeat
if i*2>num then break;
tt:=i*2;
if (i*2+1<=num) and (h[i*2+1].s<h[tt].s) then tt:=i*2+1;
tmp:=h[i].s;h[i].s:=h[tt].s;h[tt].s:=tmp;
tmp:=h[i].p;h[i].p:=h[tt].p;h[tt].p:=tmp;
wz[h[i].p]:=i;wz[h[tt].p]:=tt;
i:=tt;
until false;
end;
procedure heap_up(i:longint);
var tmp:longint;
begin
while (i<>1) and (h[i].s<h[i div 2].s) do
begin
tmp:=h[i].s;h[i].s:=h[i div 2].s;h[i div 2].s:=tmp;
tmp:=h[i].p;h[i].p:=h[i div 2].p;h[i div 2].p:=tmp;
wz[h[i].p]:=i;wz[h[i div 2].p]:=i div 2;
i:=i div 2;
end;
end;
procedure Dijkstra;
var i,k,t,min:longint;
begin
h[1].p:=0;h[1].s:=0;wz[0]:=1;
for i:=1 to n*n+1 do begin h[i+1].p:=i;h[i+1].s:=maxlongint;wz[i]:=i+1;end;
num:=n*n+2;

repeat
t:=h[1].p;min:=h[1].s;
if t=n*n+1 then begin writeln(min);break;end;
delmin;
k:=first[t];
while k<>0 do
begin
if wz[e[k]]<>0 then
if min+w[k]<h[wz[e[k]]].s then
begin
h[wz[e[k]]].s:=min+w[k];
heap_up(wz[e[k]]);
end;
k:=b[k];
end;
until false;
end;


begin
assign(input,'altitude.in');
assign(output,'altitude.out');
reset(input);rewrite(output);

read(n);
p:=0;
fillchar(b,sizeof(b),0);
fillchar(first,sizeof(first),0);
for i:=1 to n do begin read(x);add(0,i,x);end;
for i:=1 to n*(n-1) do begin read(x);add(i,i+n,x);end;
for i:=n*(n-1)+1 to n*n do begin read(x);add(i,n*n+1,x);end;
for i:=1 to n do
begin
read(x);add((i-1)*n+1,n*n+1,x);
for j:=2 to n do
begin
read(x);add((i-1)*n+j,(i-1)*n+j-1,x);
end;
read(x);add(0,i*n,x);
end;
for i:=1 to n do begin read(x);add(i,0,x);end;
for i:=1 to n*(n-1) do begin read(x);add(i+n,i,x);end;
for i:=n*(n-1)+1 to n*n do begin read(x);add(n*n+1,i,x);end;
for i:=1 to n do
begin
read(x);add(n*n+1,(i-1)*n+1,x);
for j:=2 to n do
begin
read(x);add((i-1)*n+j-1,(i-1)*n+j,x);
end;
read(x);add(i*n,0,x);
end;

Dijkstra;
close(input);close(output);
end.




