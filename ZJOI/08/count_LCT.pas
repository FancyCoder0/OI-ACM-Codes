//动态树(LCT)
//O(qlogn) 非常快
//注意:每个点的Fa不一定是splay中的Fa,还有可能是原树中的，旋转中要当心，splay判断根也是
type arr=record
         fa,l,r,sum,max,value:longint;
		 end;
var n,i,j,k,l,p,x,y,u,v,qq:longint;cc:char;s:string;
    e,b:array[-30000..30000] of longint;
    c,first,q:array[1..30000] of longint;
	a:array[0..30000] of arr;
	tp:array[1..30000] of boolean;
procedure BFS;
var i,j,k,l:longint;
begin
i:=1;j:=1;q[1]:=1;a[1].fa:=0;
repeat
k:=first[q[i]];
while k<>0 do
begin
  if e[k]<>a[q[i]].fa then
  begin
  j:=j+1;
  q[j]:=e[k];
  a[q[j]].fa:=q[i];
  end;
k:=b[k];
end;
i:=i+1;
until i>j;
end;

function maxab(a,b:longint):longint;
begin
if a>b then exit(a) else exit(b);
end;
procedure pup(i:longint);
begin
a[i].sum:=a[a[i].l].sum+a[a[i].r].sum+a[i].value;
a[i].max:=maxab(maxab(a[a[i].l].max,a[a[i].r].max),a[i].value);
end;

procedure left(i:longint);
var x,y:longint;t:boolean;
begin
  x:=a[i].r;
  y:=a[x].l;
  t:=tp[x];tp[x]:=tp[i];tp[i]:=t;
  a[i].r:=y;
  if y<>0 then a[y].fa:=i;
  if a[i].fa<>0 then
  if a[a[i].fa].l=i then a[a[i].fa].l:=x
                    else
  if a[a[i].fa].r=i then a[a[i].fa].r:=x;   /////注意
  a[x].fa:=a[i].fa;
  a[x].l:=i;
  a[i].fa:=x;

  pup(i);pup(x);
end;

procedure right(i:longint);
var x,y:longint;t:boolean;
begin
  x:=a[i].l;
  y:=a[x].r;
  t:=tp[x];tp[x]:=tp[i];tp[i]:=t;

  a[i].l:=y;
  if y<>0 then a[y].fa:=i;
  if a[i].fa<>0 then
  if a[a[i].fa].l=i then a[a[i].fa].l:=x
                    else
  if a[a[i].fa].r=i then a[a[i].fa].r:=x;   /////注意
  a[x].fa:=a[i].fa;
  a[x].r:=i;
  a[i].fa:=x;

  pup(i);pup(x);
end;

procedure splay(x,f:longint);
var y,z:longint;
begin
  while not tp[x] do                /////////注意
  begin
    y:=a[x].fa;
    z:=a[y].fa;
	if tp[y] then        /////////注意
	if a[y].l=x then right(y) else left(y)
	       else
	if a[z].l=y then
	  if a[y].l=x then begin right(z);right(y);end
	              else begin left(y);right(z);end
				else
	  if a[y].l=x then begin right(y);left(z);end
	              else begin left(z);left(y);end;
  end;
end;

function ask(x,y,c:longint):longint;
var i,sums,maxs:longint;
begin
  sums:=0;
  maxs:=-maxlongint;
  i:=0;
  while x<>0 do
  begin
   splay(x,0);                                                             ////////
   if a[x].r<>0 then tp[a[x].r]:=true;
   a[x].r:=i;if i<>0 then begin tp[i]:=false;a[i].fa:=x;end;
   pup(x);
   i:=x;x:=a[x].fa;
  end;                                                                    ////////Access过程，把X到根的路径都改为实边

  i:=0;
  while y<>0 do
  begin
   splay(y,0);
   if (a[y].fa=0) then                                          ///////////最后一步很关键
   begin
     sums:=a[i].sum+a[a[y].r].sum+a[y].value;
	 maxs:=maxab(maxab(a[i].max,a[a[y].r].max),a[y].value);
   end;
   if a[y].r<>0 then tp[a[y].r]:=true;
   a[y].r:=i;if i<>0 then begin tp[i]:=false;a[i].fa:=y;end;
   pup(y);
   i:=y;y:=a[y].fa;
  end;
 if c=0 then exit(sums) else exit(maxs);
end;
procedure Change(x,c:longint);
var t:longint;
begin
splay(x,0);
a[x].value:=c;
pup(x);
end;

begin
assign(input,'count.in');
assign(output,'count.out');
reset(input);rewrite(output);

readln(n);
for i:=1 to n-1 do
begin
readln(x,y);
e[i]:=y;
if first[x]=0 then first[x]:=i else b[c[x]]:=i;c[x]:=i;
e[-i]:=x;
if first[y]=0 then first[y]:=-i else b[c[y]]:=-i;c[y]:=-i;
end;
fillchar(a,sizeof(a),0);
BFS;
a[0].max:=-maxlongint;
a[0].sum:=0;
for i:=1 to n do read(a[i].value);
fillchar(tp,sizeof(tp),true);

readln(qq);
for l:=1 to qq do
begin
s:='';
repeat read(cc); s:=s+cc; until cc=' ';
readln(u,v);
if s='CHANGE ' then change(u,v)
               else
if s='QMAX ' then writeln(ask(u,v,1))
             else writeln(ask(u,v,0));
end;

close(input);close(output);
end.









