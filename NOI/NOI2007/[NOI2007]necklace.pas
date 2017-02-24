//线段树
//问题巧妙转化（旋转、固定翻转）找处在位置1的在线段树的哪个位置
//注意线段树整体赋值一定要下传标记！
type arr=record
               l,r,s,same:longint;
               end;
var n,c,m,i,j,k,l,p,first,xx,t,x,y,z,ans,c1,c2:longint;cc1,cc2:char;
      tree:array[1..1048576] of arr;
procedure tree_ins(i,x,y,l,r,ss:longint);
begin
if (l>y)or(r<x) then exit;
if (x>=l)and(y<=r) then begin tree[i].s:=1;tree[i].l:=ss;tree[i].r:=ss;
                              tree[i].same:=ss;
                        end
                              else
begin
if tree[i].same<>0 then
begin
tree[i*2].s:=1;tree[i*2].l:=tree[i].same;tree[i*2].r:=tree[i].same;tree[i*2].same:=tree[i].same;
tree[i*2+1].s:=1;tree[i*2+1].l:=tree[i].same;tree[i*2+1].r:=tree[i].same;tree[i*2+1].same:=tree[i].same;
tree[i].same:=0;
end;
tree_ins(i*2,x,(x+y) div 2,l,r,ss);
tree_ins(i*2+1,(x+y) div 2+1,y,l,r,ss);
tree[i].l:=tree[i*2].l;
tree[i].r:=tree[i*2+1].r;
if tree[i*2].r=tree[i*2+1].l then tree[i].s:=tree[i*2].s+tree[i*2+1].s-1
                                          else tree[i].s:=tree[i*2].s+tree[i*2+1].s;
end;
end;
procedure tree_find(i,x,y,l,r:longint);
begin
if (l>y)or(r<x) then exit;
if (x>=l)and(y<=r) then ans:=ans+tree[i].s
                              else
begin
if tree[i].same<>0 then
begin
tree[i*2].s:=1;tree[i*2].l:=tree[i].same;tree[i*2].r:=tree[i].same;tree[i*2].same:=tree[i].same;
tree[i*2+1].s:=1;tree[i*2+1].l:=tree[i].same;tree[i*2+1].r:=tree[i].same;tree[i*2+1].same:=tree[i].same;
tree[i].same:=0;
end;
tree_find(i*2,x,(x+y) div 2,l,r);
tree_find(i*2+1,(x+y) div 2+1,y,l,r);
tree[i].l:=tree[i*2].l;
tree[i].r:=tree[i*2+1].r;
if tree[i*2].r=tree[i*2+1].l then tree[i].s:=tree[i*2].s+tree[i*2+1].s-1
                                          else tree[i].s:=tree[i*2].s+tree[i*2+1].s;

if tree[i*2].r=tree[i*2+1].l then
if (l<=(x+y) div 2) and (r>=(x+y) div 2+1) then
ans:=ans-1;
end;
end;
function tree_search(i,x,y,l:longint):longint;
begin
if x=y then exit(tree[i].l);
if tree[i].same<>0 then
begin
tree[i*2].s:=1;tree[i*2].l:=tree[i].same;tree[i*2].r:=tree[i].same;tree[i*2].same:=tree[i].same;
tree[i*2+1].s:=1;tree[i*2+1].l:=tree[i].same;tree[i*2+1].r:=tree[i].same;tree[i*2+1].same:=tree[i].same;
tree[i].same:=0;
end;
if l<=(x+y) div 2 then tree_search:=tree_search(i*2,x,(x+y) div 2,l)
                  else tree_search:=tree_search(i*2+1,(x+y) div 2+1,y,l);
tree[i].l:=tree[i*2].l;
tree[i].r:=tree[i*2+1].r;
if tree[i*2].r=tree[i*2+1].l then tree[i].s:=tree[i*2].s+tree[i*2+1].s-1
                             else tree[i].s:=tree[i*2].s+tree[i*2+1].s;
end;

begin
assign(input,'necklace.in');
assign(output,'necklace.out');
reset(input);rewrite(output);
readln(n,c);
for i:=1 to n do
begin
read(x);
tree_ins(1,1,n,i,i,x);
end;
readln;
readln(m);
first:=1;xx:=1;
for i:=1 to m do
begin
read(cc1,cc2);
if cc1='R' then begin read(x);first:=(first-xx*x+n-1) mod n+1;end;
if cc1='F' then begin xx:=-xx;
                      {if first<>1 then first:=n-first+2;}end;
if cc1='S' then begin read(x,y);x:=(first+xx*(x-1)+2*n-1) mod n+1;
                                                 y:=(first+xx*(y-1)+2*n-1) mod n+1;
                                                 c1:=tree_search(1,1,n,x);
                                                 c2:=tree_search(1,1,n,y);
                                                 tree_ins(1,1,n,x,x,c2);
                                                 tree_ins(1,1,n,y,y,c1);
                       end;
if cc1='P' then begin read(x,y,z);
                                  x:=(first+xx*(x-1)+2*n-1) mod n+1;
                                  y:=(first+xx*(y-1)+2*n-1) mod n+1;
                                  if xx=-1 then begin t:=x;x:=y;y:=t;end;
                                  if x<=y then tree_ins(1,1,n,x,y,z)
                                          else begin tree_ins(1,1,n,x,n,z);tree_ins(1,1,n,1,y,z);end;
                       end;
if cc1='C' then if (cc2='S') then
                        begin read(cc2);read(x,y);
                                  x:=(first+xx*(x-1)+2*n-1) mod n+1;
                                  y:=(first+xx*(y-1)+2*n-1) mod n+1;
                                  if xx=-1 then begin t:=x;x:=y;y:=t;end;
                                  ans:=0;
                                  if x<=y then tree_find(1,1,n,x,y)
                                               else begin tree_find(1,1,n,x,n);tree_find(1,1,n,1,y);
                                                          if tree_search(1,1,n,n)=tree_search(1,1,n,1) then ans:=ans-1;
                                                    end;
                                  writeln(ans);
                        end
                                          else
                       begin
                       if tree[1].s=1 then writeln(1)
                                          else begin if tree[1].l=tree[1].r then writeln(tree[1].s-1) else writeln(tree[1].s);end;
                       end;
readln;
end;
close(input);close(output);
end.



