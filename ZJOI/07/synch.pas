//BFS
var n,root,i,j,k,l,p,x,y,z:longint;ans,tmp:int64;zz:boolean;
    e,b,w:array[1..1000000] of longint;
    c,first,f,path,fa:array[1..600000] of longint;
    tt,max:array[1..600000] of int64;
begin
assign(input,'synch.in');
assign(output,'synch.out');
reset(input);rewrite(output);

readln(n);
readln(root);
fillchar(first,sizeof(first),0);
fillchar(b,sizeof(b),0);
for i:=1 to n-1 do
begin
read(x,y,z);
e[i*2-1]:=y;w[i*2-1]:=z;
e[i*2]:=x;w[i*2]:=z;
if first[x]=0 then first[x]:=i*2-1 else b[c[x]]:=i*2-1;c[x]:=i*2-1;
if first[y]=0 then first[y]:=i*2 else b[c[y]]:=i*2;c[y]:=i*2;
end;

for i:=1 to n do max[i]:=-maxlongint*maxlongint;
i:=1;j:=1;f[1]:=root;path[1]:=0;fa[1]:=0;
repeat
k:=first[f[i]];
zz:=true;
while k<>0 do
begin
if e[k]<>fa[i] then
begin
zz:=false;
j:=j+1;
f[j]:=e[k];
path[j]:=k;
fa[j]:=f[i];
end;
k:=b[k];
end;
if zz then max[f[i]]:=0;
i:=i+1;
until i>j;

for i:=n downto 1 do
if max[f[i]]+w[path[i]]>max[fa[i]] then max[fa[i]]:=max[f[i]]+w[path[i]];

ans:=0;
tt[root]:=max[root];
for i:=1 to n do
begin
k:=first[f[i]];
while k<>0 do
begin
if e[k]<>fa[i] then
begin
tmp:=tt[f[i]]-w[k]-max[e[k]];
ans:=ans+tmp;
tt[e[k]]:=tt[f[i]]-w[k]-tmp;
end;
k:=b[k];
end;
end;

writeln(ans);
close(input);close(output);
end.














