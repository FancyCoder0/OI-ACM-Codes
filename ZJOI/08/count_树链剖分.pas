//路径剖分+LCA+线段树 常数大
//时间O(n(logn)^2)
var n,qq,i,j,k,l,p,x,y,num,LCAxy:longint;cc,c1:char;
    a,first,c,max,hfa,d,u,f,tp,q:array[1..30000] of longint;
    v,o:array[1..30000] of boolean;
    LCAfa:array[1..30000,0..15] of longint;
    e,b:array[1..60000] of longint;
    tree,tree2:array[1..100000] of longint;
    log_2:array[1..40000] of longint;
function maxab(a,b:longint):longint;
begin
if a>b then exit(a) else exit(b);
end;
procedure BFS;
var i,j,k,t,l,time:longint;
begin
fillchar(v,sizeof(v),false);
i:=1;j:=1;f[1]:=1;tp[1]:=1;
repeat
k:=first[f[i]];
while k<>0 do
begin
if tp[e[k]]=0 then
begin
j:=j+1;
f[j]:=e[k];
tp[e[k]]:=j;
end;
k:=b[k];
end;
i:=i+1;
until i>j;
for i:=n downto 1 do
begin
u[f[i]]:=1;j:=-maxlongint;
k:=first[f[i]];
while k<>0 do
begin
if i<tp[e[k]] then begin u[f[i]]:=u[f[i]]+u[e[k]];
                         if u[e[k]]>j then begin j:=u[e[k]];max[f[i]]:=e[k];end;
                   end;
k:=b[k];
end;
end;

fillchar(v,sizeof(v),false);
i:=1;j:=1;
f[1]:=1;hfa[1]:=0;d[1]:=1;v[1]:=true;LCAfa[1][0]:=0;
repeat
for k:=1 to 15 do
if d[f[i]]-1 shl k>0 then LCAfa[f[i]][k]:=LCAfa[LCAfa[f[i]][k-1]][k-1];

if max[f[i]]<>0 then
begin
j:=j+1;f[j]:=max[f[i]];v[f[j]]:=true;if hfa[f[i]]=0 then hfa[f[j]]:=f[i] else hfa[f[j]]:=hfa[f[i]];d[f[j]]:=d[f[i]]+1;LCAfa[f[j]][0]:=f[i];
end;
k:=first[f[i]];
while k<>0 do
begin
if not v[e[k]] then begin j:=j+1;f[j]:=e[k];v[f[j]]:=true;hfa[f[j]]:=0;d[f[j]]:=d[f[i]]+1;LCAfa[f[j]][0]:=f[i];end;
k:=b[k];
end;
i:=i+1;
until i>j;

fillchar(v,sizeof(v),false);
fillchar(o,sizeof(o),true);
time:=1;
i:=1;f[1]:=1;
q[1]:=1;v[1]:=true;
repeat
if o[f[i]] then
begin
o[f[i]]:=false;
if max[f[i]]<>0 then
begin
time:=time+1;q[max[f[i]]]:=time;
v[max[f[i]]]:=true;
f[i+1]:=max[f[i]];
i:=i+1;
end;
end
else
while first[f[i]]<>0 do
if not v[e[first[f[i]]]] then
begin
time:=time+1;q[e[first[f[i]]]]:=time;
v[e[first[f[i]]]]:=true;
f[i+1]:=e[first[f[i]]];
first[f[i]]:=b[first[f[i]]];
i:=i+1;
break;
end else first[f[i]]:=b[first[f[i]]];
if first[f[i]]=0 then i:=i-1;
until i=0;
end;
function LCA(x,y:longint):longint;
var k,l:longint;
begin
if d[x]>d[y] then
begin
k:=d[x]-d[y];l:=0;
while k<>0 do
begin
if odd(k) then x:=LCAfa[x][l];
k:=k shr 1;l:=l+1;
end;
end
             else
begin
k:=d[y]-d[x];l:=0;
while k<>0 do
begin
if odd(k) then y:=LCAfa[y][l];
k:=k shr 1;l:=l+1;
end;
end;
if x=y then exit(x);
for k:=log_2[d[x]-1] downto 0 do
if LCAfa[x][k]<>LCAfa[y][k] then begin x:=LCAfa[x][k];y:=LCAfa[y][k];end;
exit(LCAfa[x][0]);
end;

procedure tree_ins(i,x,y,l,s:longint);
begin
repeat
tree[i]:=tree[i]+s;
if x=y then break;
if l<=(x+y) shr 1 then begin i:=i shl 1;y:=(x+y) shr 1;end
                  else begin i:=i shl 1+1;x:=(x+y) shr 1+1;end;
until false;
end;
function tree_sum(i,x,y,l,r:longint):longint;
begin
if (l>y) or (r<x) then exit(0)
                  else
if (x>=l) and (y<=r) then exit(tree[i])
                     else tree_sum:=tree_sum(i shl 1,x,(x+y) shr 1,l,r)+tree_sum(i shl 1+1,(x+y) shr 1+1,y,l,r);
end;
procedure tree2_ins(i,x,y,l,s:longint);
begin
repeat
if s>tree2[i] then tree2[i]:=s;
if x=y then break;
if l<=(x+y) shr 1 then begin i:=i shl 1;y:=(x+y) shr 1;end
                  else begin i:=i shl 1+1;x:=(x+y) shr 1+1;end;
until false;
end;
function tree2_find(i,x,y,l,r:longint):longint;
begin
if l>r then exit(-maxlongint);
if (l>y) or (r<x) then exit(-maxlongint)
                  else
if (x>=l) and (y<=r) then exit(tree2[i])
                     else tree2_find:=maxab(tree2_find(i shl 1,x,(x+y) shr 1,l,r),tree2_find(i shl 1+1,(x+y) shr 1+1,y,l,r));
end;
procedure tree2_delete(i,x,y,l:longint);
begin
repeat
tree2[i]:=maxab(tree2_find(1,1,n,x,l-1),tree2_find(1,1,n,l+1,y));
if x=y then break;
if l<=(x+y) shr 1 then begin i:=i shl 1;y:=(x+y) shr 1;end
                  else begin i:=i shl 1+1;x:=(x+y) shr 1+1;end;
until false;
end;

function dis(i:longint):longint;
begin
dis:=a[LCAxy];
while i<>LCAxy do
if hfa[i]<>0 then begin if q[hfa[i]]>=q[LCAxy] then begin dis:=dis+tree_sum(1,1,n,q[hfa[i]]+1,q[i]);i:=hfa[i];end
                                               else begin dis:=dis+tree_sum(1,1,n,q[LCAxy]+1,q[i]);i:=LCAxy;end;
                  end
        else begin dis:=dis+a[i];i:=LCAfa[i][0];end;
end;
function qmax(i:longint):longint;
begin
qmax:=a[LCAxy];
while i<>LCAxy do
if hfa[i]<>0 then begin if q[hfa[i]]>=q[LCAxy] then begin qmax:=maxab(qmax,tree2_find(1,1,n,q[hfa[i]]+1,q[i]));i:=hfa[i];end
                                               else begin qmax:=maxab(qmax,tree2_find(1,1,n,q[LCAxy]+1,q[i]));i:=LCAxy;end;
                  end
        else begin qmax:=maxab(qmax,a[i]);i:=LCAfa[i][0];end;
end;

begin
assign(input,'count.in');
assign(output,'count.out');
reset(input);rewrite(output);

for i:=0 to 14 do
for j:=1 shl i to 1 shl (i+1)-1 do
log_2[j]:=i;

read(n);
for i:=1 to n-1 do
begin
read(x,y);
e[i shl 1-1]:=y;if first[x]=0 then first[x]:=i shl 1-1 else b[c[x]]:=i shl 1-1;c[x]:=i shl 1-1;
e[i shl 1]:=x;if first[y]=0 then first[y]:=i shl 1 else b[c[y]]:=i shl 1;c[y]:=i shl 1;
end;

BFS;

fillchar(tree2,sizeof(tree2),128);
for i:=1 to n do begin read(a[i]);tree_ins(1,1,n,q[i],a[i]);
                                  tree2_ins(1,1,n,q[i],a[i]);
                 end;
readln(qq);
for i:=1 to qq do
begin
read(cc,c1);
if cc='C' then begin read(c1,c1,c1,c1,c1);readln(x,y);tree_ins(1,1,n,q[x],y-a[x]);a[x]:=y;
                                                      tree2_delete(1,1,n,q[x]);tree2_ins(1,1,n,q[x],a[x]);
               end
          else
if c1='S' then
begin
read(cc,cc,cc);
readln(x,y);
LCAxy:=LCA(x,y);
writeln(dis(x)+dis(y)-a[LCAxy]);
end
          else
begin
read(cc,cc,cc);
readln(x,y);
LCAxy:=LCA(x,y);
writeln(maxab(qmax(x),qmax(y)));
end;
end;
close(input);close(output);
end.








