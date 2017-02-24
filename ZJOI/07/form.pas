//两棵Treap 常数大
const root=1500001;
var n,m,i,j,k,l,p,min,tmp,x,y,num1,num2,ss1,ss2:longint;cc,c1:char;
        a,c:array[1..500000] of longint;
        tree1:array[0..1500001] of record
                                                              s,l,r,p:longint;end;
        tree2:array[0..1500001] of record
                                                               s,l,r,size,p:longint;end;
function tree1_XZR(i:longint):longint;
var x,y:longint;
begin
x:=tree1[i].l;
y:=tree1[x].r;
tree1[i].l:=y;
tree1[x].r:=i;
exit(x);
end;
function tree1_XZL(i:longint):longint;
var x,y:longint;
begin
x:=tree1[i].r;
y:=tree1[x].l;
tree1[i].r:=y;
tree1[x].l:=i;
exit(x);
end;
function tree1_ins(i,x:longint):longint;
begin
if i=0 then begin num1:=num1+1;ss1:=ss1+1;tree1[ss1].s:=x;tree1[ss1].p:=random(100000)+1;exit(ss1);end;
if x<tree1[i].s then begin tree1[i].l:=tree1_ins(tree1[i].l,x);if tree1[tree1[i].l].p>tree1[i].p then i:=tree1_XZR(i);exit(i);end
                             else begin tree1[i].r:=tree1_ins(tree1[i].r,x);if tree1[tree1[i].r].p>tree1[i].p then i:=tree1_XZL(i);exit(i);end;
end;
function tree1_delete(i,x:longint):longint;
begin
if x<tree1[i].s then begin tree1[i].l:=tree1_delete(tree1[i].l,x);exit(i);end;
if x>tree1[i].s then begin tree1[i].r:=tree1_delete(tree1[i].r,x);exit(i);end;
if (tree1[i].l=0) and (tree1[i].r=0) then begin dec(num1);tree1[i].s:=0;tree1[i].p:=0;exit(0);end;
if tree1[tree1[i].l].p>tree1[tree1[i].r].p then begin i:=tree1_XZR(i);tree1[i].r:=tree1_delete(tree1[i].r,x);exit(i);end
                                           else begin i:=tree1_XZL(i);tree1[i].l:=tree1_delete(tree1[i].l,x);exit(i);end;
end;
function tree1_findmin:longint;
var t:longint;
begin
t:=tree1[root].r;
while tree1[t].l<>0 do t:=tree1[t].l;
exit(tree1[t].s);
end;
//////////////////
function tree2_XZR(i:longint):longint;
var x,y:longint;
begin
x:=tree2[i].l;
y:=tree2[x].r;
tree2[i].l:=y;
tree2[x].r:=i;
tree2[i].size:=tree2[tree2[i].l].size+tree2[tree2[i].r].size+1;
tree2[x].size:=tree2[tree2[x].l].size+tree2[tree2[x].r].size+1;
exit(x);
end;
function tree2_XZL(i:longint):longint;
var x,y:longint;
begin
x:=tree2[i].r;
y:=tree2[x].l;
tree2[i].r:=y;
tree2[x].l:=i;
tree2[i].size:=tree2[tree2[i].l].size+tree2[tree2[i].r].size+1;
tree2[x].size:=tree2[tree2[x].l].size+tree2[tree2[x].r].size+1;
exit(x);
end;
function tree2_ins(i,x:longint):longint;
begin
if i=0 then begin num2:=num2+1;ss2:=ss2+1;tree2[ss2].s:=x;tree2[ss2].size:=1;tree2[ss2].p:=random(100000)+1;exit(ss2);end;
inc(tree2[i].size);
if x<tree2[i].s then begin tree2[i].l:=tree2_ins(tree2[i].l,x);if tree2[tree2[i].l].p>tree2[i].p then i:=tree2_XZR(i);exit(i);end
                             else begin tree2[i].r:=tree2_ins(tree2[i].r,x);if tree2[tree2[i].r].p>tree2[i].p then i:=tree2_XZL(i);exit(i);end;
end;
function tree2_rank(x:longint):longint;
var t:longint;
begin
tree2_rank:=-1;
t:=root;
while tree2[t].s<>x do
if x<tree2[t].s then t:=tree2[t].l
                             else begin tree2_rank:=tree2_rank+tree2[tree2[t].l].size+1;t:=tree2[t].r;end;
tree2_rank:=tree2_rank+tree2[tree2[t].l].size+1;
end;
function tree2_find(i:longint):longint;
begin
tree2_find:=root;i:=i+1;
while i<>tree2[tree2[tree2_find].l].size+1 do
if i<tree2[tree2[tree2_find].l].size+1 then tree2_find:=tree2[tree2_find].l
                                       else begin i:=i-(tree2[tree2[tree2_find].l].size+1);tree2_find:=tree2[tree2_find].r;end;
end;

begin
assign(input,'form.in');
assign(output,'form.out');
reset(input);rewrite(output);

ss1:=0;num1:=1;tree1[root].s:=-maxlongint;tree1[root].p:=maxlongint;
ss2:=0;num2:=1;tree2[root].s:=-maxlongint;tree2[root].p:=maxlongint;tree2[root].size:=1;

readln(n,m);
for i:=1 to n do read(a[i]);readln;
c:=a;
for i:=2 to n do tree1_ins(root,abs(a[i]-a[i-1]));
min:=maxlongint;
for i:=1 to n do tree2_ins(root,a[i]);
for i:=1 to n do
begin
x:=tree2_rank(a[i]);
if x>1 then begin tmp:=abs(a[i]-tree2[tree2_find(x-1)].s);if tmp<min then min:=tmp;end;
if x<num2-1 then begin tmp:=abs(a[i]-tree2[tree2_find(x+1)].s);if tmp<min then min:=tmp;end;
end;
for i:=1 to m do
begin
read(cc);
if cc='I' then begin read(c1,c1,c1,c1,c1,c1);readln(x,y);
                                       if x<n then begin tree1_delete(root,abs(c[x]-a[x+1]));tree1_ins(root,abs(y-a[x+1]));end;
                                       tree1_ins(root,abs(y-c[x]));c[x]:=y;

                                      tree2_ins(root,y);
                                      x:=tree2_rank(y);
                                      if x>1 then begin tmp:=abs(y-tree2[tree2_find(x-1)].s);if tmp<min then min:=tmp;end;
                                      if x<num2-1 then begin tmp:=abs(y-tree2[tree2_find(x+1)].s);if tmp<min then min:=tmp;end;


                           end
               else
begin
read(c1,c1,c1,c1);
if c1='S' then writeln(min)
          else writeln(tree1_findmin());
readln;
end;
end;
close(input);close(output);
end.
