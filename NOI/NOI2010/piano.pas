//Ïß¶ÎÊ÷+¶Ñ
type arr=record
                   ss,p,px,py,pmax:longint;
                   end;
var n,k,l,r,i,j,num,max,max1:longint;ans:int64;
        tree,en:array[1..1200000] of longint;
        a:array[1..1200000] of arr;
        c:array[1..500000] of longint;
        s:array[0..500000] of longint;
        dmax:arr;
function min(a,b:longint):longint;
begin
if a<b then exit(a) else exit(b);
end;
procedure tree_ins(i,x,y,l,s:longint);
begin
if s>tree[i] then begin tree[i]:=s;en[i]:=l;end;
if x<>y then
if l<=(x+y) div 2 then tree_ins(i*2,x,(x+y) div 2,l,s)
                                  else tree_ins(i*2+1,(x+y) div 2+1,y,l,s);
end;
procedure tree_find(i,x,y,l,r:longint);
begin
if (l>y) or (r<x) then exit
                                 else
if (x>=l) and (y<=r) then begin if tree[i]>max then begin max:=tree[i];max1:=en[i];end;end
                                          else
begin
tree_find(i*2,x,(x+y) div 2,l,r);
tree_find(i*2+1,(x+y) div 2+1,y,l,r);
end;
end;
procedure heap_up(i:longint);
var tmp:arr;
begin
while (i<>1) and (a[i].ss>a[i div 2].ss) do
begin
tmp:=a[i];a[i]:=a[i div 2];a[i div 2]:=tmp;
i:=i div 2;
end;
end;
procedure heap_down(i:longint);
var t:longint;tmp:arr;
begin
repeat
if i*2>num then break;
t:=i*2;
if (i*2+1<=num) and (a[i*2].ss<a[i*2+1].ss) then t:=i*2+1;
if a[i].ss>=a[t].ss then break;
tmp:=a[i];a[i]:=a[t];a[t]:=tmp;
i:=t;
until false;
end;

begin
assign(input,'piano.in');
assign(output,'piano.out');
reset(input);rewrite(output);

readln(n,k,l,r);
for i:=1 to n do readln(c[i]);
s[0]:=0;for i:=1 to n do s[i]:=s[i-1]+c[i];
fillchar(tree,sizeof(tree),128);
for i:=1 to n do tree_ins(1,1,n,i,s[i]);
num:=0;
for i:=1 to n do
if i+l-1<=n then
begin
max:=-maxlongint;
tree_find(1,1,n,i+l-1,min(i+r-1,n));
inc(num);
a[num].ss:=max-s[i-1];
a[num].p:=i;
a[num].px:=i+l-1;
a[num].py:=min(i+r-1,n);
a[num].pmax:=max1;
heap_up(num);
end;
ans:=0;
for i:=1 to k do
begin
ans:=ans+a[1].ss;
dmax:=a[1];
a[1]:=a[num];
dec(num);
heap_down(1);

if dmax.pmax-1>=dmax.px then
begin
max:=-maxlongint;
tree_find(1,1,n,dmax.px,dmax.pmax-1);
inc(num);
a[num].ss:=max-s[dmax.p-1];
a[num].p:=dmax.p;
a[num].px:=dmax.px;
a[num].py:=dmax.pmax-1;
a[num].pmax:=max1;
heap_up(num);
end;
if dmax.pmax+1<=dmax.py then
begin
max:=-maxlongint;
tree_find(1,1,n,dmax.pmax+1,dmax.py);
inc(num);
a[num].ss:=max-s[dmax.p-1];
a[num].p:=dmax.p;
a[num].px:=dmax.pmax+1;
a[num].py:=dmax.py;
a[num].pmax:=max1;
heap_up(num);
end;
end;

writeln(ans);
close(input);close(output);
end.










