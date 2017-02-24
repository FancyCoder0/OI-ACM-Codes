//LCT O(mlogn)
const oo=maxlongint div 2;
      maxn=30000;
var n,m,i,j,k,p,tmp,x,y,l1,l2,r1,r2,t1:longint;cc,cc2,x1,x2:char;pp1,pp2,t:boolean;
    e,b:array[-maxn..maxn] of longint;
    first,last,q:array[1..maxn] of longint;
    fa,l,r:array[0..maxn+3] of longint;
        tp:array[0..maxn+3] of boolean;
         c:array[0..maxn+3,1..2] of boolean;
     lx,rx:array[0..maxn+3,1..2] of longint;
     ll,rr:array[0..maxn+3,1..2,1..2] of longint;
function max(a,b:longint):longint;
begin
  if a>b then exit(a) else exit(b);
end;

procedure BFS;
var i,j,k:longint;
begin
  i:=1;j:=1;q[1]:=1;
  repeat
    k:=first[q[i]];
    while k<>0 do begin
      if e[k]<>fa[q[i]] then begin
        j:=j+1;
        q[j]:=e[k];
        fa[q[j]]:=q[i];
      end;
    k:=b[k];
    end;
    i:=i+1;
  until i>j;
end;

procedure pup(i:longint);
begin
  ll[i]:=ll[maxn+3];
  rr[i]:=rr[maxn+3];
  lx[i]:=lx[maxn+3];
  rx[i]:=rx[maxn+3];
  //两颗子树连接起来
  for l2:=1 to 2 do
    if c[i][l2] then
      for r1:=1 to 2 do
        if c[i][r1] then
         for l1:=1 to 2 do
           for r2:=1 to 2 do
             if ((l[i]<>0)or(c[i][l1]))and
                ((r[i]<>0)or(c[i][r2]))then begin
               if ll[l[i]][l1][l2]+ll[r[i]][r1][r2]+ord(l2<>r1)+1>ll[i][l1][r2] then
                 ll[i][l1][r2]:=ll[l[i]][l1][l2]+ll[r[i]][r1][r2]+ord(l2<>r1)+1;
	       if ll[i][l1][r2]>lx[i][l1] then lx[i][l1]:=ll[i][l1][r2];
               if rr[r[i]][r2][r1]+rr[l[i]][l2][l1]+ord(r1<>l2)+1>rr[i][r2][l1] then
                 rr[i][r2][l1]:=rr[r[i]][r2][r1]+rr[l[i]][l2][l1]+ord(r1<>l2)+1;
	       if rr[i][r2][l1]>rx[i][r2] then rx[i][r2]:=rr[i][r2][l1];
             end;
  //连接一个子树
  for l2:=1 to 2 do
    if c[i][l2] then
      for t1:=1 to 2 do
        if c[i][t1] then
          for l1:=1 to 2 do begin
            if ((l[i]<>0)or(c[i][l1])) then
              if ll[l[i]][l1][l2]+ord(l2<>t1)+1+lx[r[i]][t1]>lx[i][l1] then
                lx[i][l1]:=ll[l[i]][l1][l2]+ord(l2<>t1)+1+lx[r[i]][t1];
            if ((r[i]<>0)or(c[i][l1])) then
              if rr[r[i]][l1][l2]+ord(l2<>t1)+1+rx[l[i]][t1]>rx[i][l1] then
                rx[i][l1]:=rr[r[i]][l1][l2]+ord(l2<>t1)+1+rx[l[i]][t1];
          end;
  //取其中一颗子树的最大值
  for l1:=1 to 2 do
    if lx[l[i]][l1]>lx[i][l1] then
      lx[i][l1]:=lx[l[i]][l1];
  for r1:=1 to 2 do
    if rx[r[i]][r1]>rx[i][r1] then
      rx[i][r1]:=rx[r[i]][r1];
end;
procedure left(i:longint);
var x,y:longint;
begin
  x:=r[i];
  y:=l[x];
  r[i]:=y;
  fa[y]:=i;
  if l[fa[i]]=i then l[fa[i]]:=x
                else
  if r[fa[i]]=i then r[fa[i]]:=x;
  fa[x]:=fa[i];
  l[x]:=i;
  fa[i]:=x;
  t:=tp[i];tp[i]:=tp[x];tp[x]:=t;
  pup(i);
end;

procedure right(i:longint);
var x,y:longint;
begin
  x:=l[i];
  y:=r[x];
  l[i]:=y;
  fa[y]:=i;
  if l[fa[i]]=i then l[fa[i]]:=x
                else
  if r[fa[i]]=i then r[fa[i]]:=x;
  fa[x]:=fa[i];
  r[x]:=i;
  fa[i]:=x;
  t:=tp[i];tp[i]:=tp[x];tp[x]:=t;
  pup(i);
end;

procedure splay(x,f:longint);
var y,z:longint;
begin
  while not tp[x] do begin
    y:=fa[x];
    z:=fa[y];
    if tp[y] then
      if l[y]=x then right(y) else left(y)
                else
      if l[z]=y then
        if l[y]=x then begin right(z);right(y);end
                  else begin left(y);right(z);end
                else
        if l[y]=x then begin right(y);left(z);end
                  else begin left(z);left(y);end;
  end;
  pup(x);
end;

procedure change(i:longint;x1,x2:boolean);
begin
  splay(i,0);
  c[i][1]:=x1;
  c[i][2]:=x2;
  pup(i);
end;

procedure ask(x,y:longint);
var i:longint;
begin
  i:=0;
  while x<>0 do begin
    splay(x,0);
    tp[r[x]]:=true;
    r[x]:=i;tp[i]:=false;fa[i]:=x;
    pup(x);
    i:=x;x:=fa[x];
  end;

  i:=0;
  while y<>0 do begin
    splay(y,0);
    if fa[y]=0 then begin
      c[maxn+1]:=c[y];
      ll[maxn+1]:=ll[y];
      rr[maxn+1]:=rr[y];
      lx[maxn+1]:=lx[y];
      rx[maxn+1]:=rx[y];
      l[maxn+1]:=0;
      r[maxn+1]:=0;
      if r[y]>0 then begin
        c[maxn+2]:=c[r[y]];
        ll[maxn+2]:=rr[r[y]];
        rr[maxn+2]:=ll[r[y]];
        lx[maxn+2]:=rx[r[y]];
        rx[maxn+2]:=lx[r[y]];
        l[maxn+1]:=maxn+2;
      end;
      if i>0 then r[maxn+1]:=i;
      pup(maxn+1);
      writeln(max(lx[maxn+1][1],lx[maxn+1][2]));
    end;
    tp[r[y]]:=true;
    r[y]:=i;tp[i]:=false;fa[i]:=y;
    pup(y);
    i:=y;y:=fa[y];
  end;
end;

begin
  assign(input,'fight.in');
  assign(output,'fight.out');
  reset(input);rewrite(output);

  readln(n,m);
  for i:=1 to n-1 do begin
    readln(x,y);
    e[i]:=y;
    if first[x]=0 then first[x]:=i else b[last[x]]:=i;last[x]:=i;
    e[-i]:=x;
    if first[y]=0 then first[y]:=-i else b[last[y]]:=-i;last[y]:=-i;
  end;
  c[0][1]:=false;
  c[0][2]:=false;
  ll[0][1][1]:=0;
  ll[0][1][2]:=-oo;
  ll[0][2][1]:=-oo;
  ll[0][2][2]:=0;
  rr[0][1][1]:=0;
  rr[0][1][2]:=-oo;
  rr[0][2][1]:=-oo;
  rr[0][2][2]:=0;
  lx[0][1]:=0;
  lx[0][2]:=0;
  rx[0][1]:=0;
  rx[0][2]:=0;
  ll[maxn+3][1][1]:=-oo;
  ll[maxn+3][1][2]:=-oo;
  ll[maxn+3][2][1]:=-oo;
  ll[maxn+3][2][2]:=-oo;
  rr[maxn+3][1][1]:=-oo;
  rr[maxn+3][1][2]:=-oo;
  rr[maxn+3][2][1]:=-oo;
  rr[maxn+3][2][2]:=-oo;
  lx[maxn+3][1]:=0;
  lx[maxn+3][2]:=0;
  rx[maxn+3][1]:=0;
  rx[maxn+3][2]:=0;

  BFS;
  for i:=1 to n do begin
   readln(x1,x2);
   if x1='.' then c[i][1]:=true else c[i][2]:=false;
   if x2='.' then c[i][2]:=true else c[i][2]:=false;
   tp[i]:=true;
  end;

  for i:=1 to m do begin
    read(cc,cc2);
    if cc='Q' then begin
      readln(x,y);
      ask(x,y);
    end
    else begin
      readln(x,cc2,x1,x2);
      if x1='.' then pp1:=true else pp1:=false;
      if x2='.' then pp2:=true else pp2:=false;
      change(x,pp1,pp2);
    end;
  end;

  close(input);close(output);
end.



