//将一个图K分 求K的最大值和最小值
//要弄双向边
//所有的环长度的最大公约数为最大值
//没有环要考虑最长路
//最小值是最大值的一个最小非1约数
//考虑要全面！
var n,m,i,j,k,l,p,x,y,ans1,ans2,ttt,zzz,maxs,mins,qq:longint;pd:boolean;
    e,b,f:array[-1000000..1000000] of longint;
    first,c:array[1..100000] of longint;
    min,time:array[1..100000] of longint;
    ex:array[0..100000] of longint;
function gcd(a,b:longint):longint;
begin
if b=0 then exit(a) else exit(gcd(b,a mod b));
end;
function minab(a,b:longint):longint;
begin
if a<b then exit(a) else exit(b);
end;
function maxab(a,b:longint):longint;
begin
if a>b then exit(a) else exit(b);
end;


begin
assign(input,'party.in');
assign(output,'party.out');
reset(input);rewrite(output);

readln(n,m);
for i:=1 to m do
begin
readln(x,y);
e[i]:=y;
if first[x]=0 then first[x]:=i else b[c[x]]:=i;c[x]:=i;
e[-i]:=x;
if first[y]=0 then first[y]:=-i else b[c[y]]:=-i;c[y]:=-i;
end;

ans1:=-1;ans2:=-1;zzz:=0;
filldword(time,sizeof(time) div 4,maxlongint);
ttt:=0;
for l:=1 to n do
if time[l]=maxlongint then
begin
i:=1;j:=1;f[1]:=l;time[l]:=1;mins:=maxlongint;maxs:=-maxlongint;
repeat
k:=first[f[i]];
while k<>0 do
begin
if k>0 then if time[e[k]]=maxlongint then begin time[e[k]]:=time[f[i]]+1; j:=j+1;f[j]:=e[k];end
                                     else ttt:=gcd(ttt,abs(time[f[i]]+1-time[e[k]]))
       else if time[e[k]]=maxlongint then begin time[e[k]]:=time[f[i]]-1; j:=j+1;f[j]:=e[k];end
                                     else ttt:=gcd(ttt,abs(time[f[i]]-1-time[e[k]]));
k:=b[k];
end;
if time[f[i]]>maxs then maxs:=time[f[i]];
if time[f[i]]<mins then mins:=time[f[i]];
i:=i+1;
until i>j;
if ttt=0 then zzz:=zzz+maxs-mins+1;
end;

if ttt>=3 then
begin
ans1:=ttt;
if (ttt mod 2=0)and(ttt div 2>=3) then qq:=ttt div 2 else qq:=ttt;
for i:=3 to trunc(sqrt(ttt)) do
if ttt mod i=0 then begin if i<qq then qq:=i;break;end;
ans2:=qq;
end;

if ans1=-1 then
if zzz>=3 then writeln(zzz,' ',3)
          else writeln(ans1,' ',ans2)
           else writeln(ans1,' ',ans2);

close(input);close(output);
end.













