//80分 本地测栈溢出
//强连通后求最长路
//{$M 5000000}
var n,m,PP,i,j,k,l,x,y,dd,p,ans,ans2:longint;t:longint;
      e,ee,ee2,b,bb,bb2:array[1..2000000] of longint;
      first,ffirst,ffirst2,c,cc,cc2:array[1..100000] of longint;
      a,f,f2,time,color:array[0..100000] of longint;
      v:array[1..100000] of boolean;
      hash:array[0..999983] of longint;
      hash2:array[0..999983,1..4,1..2] of longint;
function hash_p(x,y:int64):boolean;
var i:longint;
begin
t:=(x*(n+1)+y) mod 999983;
for i:=1 to hash[t] do
if (hash2[t,i,1]=x)and(hash2[t,i,2]=y) then exit(false);
inc(hash[t]);
hash2[t,hash[t],1]:=x;
hash2[t,hash[t],2]:=y;
exit(true);
end;


procedure DFS1(i:longint);
begin
v[i]:=true;
while ffirst[i]<>0 do
begin
if not v[ee[ffirst[i]]] then DFS1(ee[ffirst[i]]);
ffirst[i]:=bb[ffirst[i]];
end;
inc(time[0]);
time[time[0]]:=i;
end;
procedure DFS2(i:longint);
begin
color[i]:=dd;inc(a[dd]);
while ffirst2[i]<>0 do
begin
if color[ee2[ffirst2[i]]]=0 then DFS2(ee2[ffirst2[i]]);
ffirst2[i]:=bb2[ffirst2[i]];
end;
end;
procedure add(x,y:longint);
begin
//writeln(x,' ',y);
p:=p+1;
e[p]:=y;
if first[x]=0 then first[x]:=p else b[c[x]]:=p;c[x]:=p;
end;
procedure search(i:longint);
begin
f[i]:=a[i];f2[i]:=1;
while first[i]<>0 do
begin
if f[e[first[i]]]=0 then search(e[first[i]]);
if f[e[first[i]]]+a[i]>f[i] then begin f[i]:=f[e[first[i]]]+a[i];
                                       f2[i]:=f2[e[first[i]]];
                                       end
                            else
if f[e[first[i]]]+a[i]=f[i] then f2[i]:=(f2[i]+f2[e[first[i]]]) mod PP;

first[i]:=b[first[i]];
end;

end;



begin
assign(input,'semi.in');
assign(output,'semi.out');
reset(input);rewrite(output);
readln(n,m,PP);
for i:=1 to m do
begin
readln(x,y);
ee[i]:=y;
if ffirst[x]=0 then ffirst[x]:=i else bb[cc[x]]:=i;cc[x]:=i;
ee2[i]:=x;
if ffirst2[y]=0 then ffirst2[y]:=i else bb2[cc2[y]]:=i;cc2[y]:=i;
end;
fillchar(v,sizeof(v),false);
fillchar(time,sizeof(time),0);
for i:=1 to n do if not v[i] then DFS1(i);
fillchar(color,sizeof(color),0);
dd:=0;
for i:=time[0] downto 1 do if color[time[i]]=0 then
begin
inc(dd);
DFS2(time[i]);
//write(a[dd],' ');
end;
//writeln;
p:=0;
for i:=1 to m do
if color[ee[i]]<>color[ee2[i]] then
if hash_p(color[ee2[i]],color[ee[i]]) then add(color[ee2[i]],color[ee[i]]);

fillchar(f,sizeof(f),0);
fillchar(f2,sizeof(f2),0);
ans:=0;ans2:=0;
for i:=1 to dd do
if f[i]=0 then
begin
search(i);
if f[i]>ans then begin ans:=f[i];ans2:=f2[i];end
            else
if f[i]=ans then ans2:=(ans2+f2[i]) mod PP;
end;
writeln(ans);
writeln(ans2 mod PP);
close(input);close(output);
end.




