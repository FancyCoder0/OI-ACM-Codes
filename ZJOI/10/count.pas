//较繁琐的模拟 需细心
var a,b:string;aa,bb:int64;
    i,j,k,l,p:longint;t:int64;
    tot,tot2:array[0..9] of int64;
    z:array[0..13] of int64;  ///0..99999(i个9)
function f10(i:longint):int64;
var t:longint;
begin
f10:=1;
for t:=1 to i do f10:=f10*10;
end;
procedure work1(x:int64);
var s:string;
    i,j,k,l:longint;
begin
str(x,s);
for i:=0 to ord(s[1])-ord('0')-1 do
begin
for j:=0 to 9 do inc(tot[j],z[length(s)-1]);
inc(tot[i],f10(length(s)-1));
end;
dec(tot[0],length(s));
for i:=1 to length(s) do inc(tot[ord(s[i])-ord('0')]);
end;
procedure work2(x:int64);
var s:string;tt:int64;
    i,j,k,l:longint;
begin
str(x,s);
for i:=0 to ord(s[1])-ord('0')-1 do
begin
for j:=0 to 9 do inc(tot[j],z[length(s)-1]);
inc(tot[i],f10(length(s)-1));
end;
dec(tot[0],length(s));
for i:=1 to length(s) do inc(tot[ord(s[i])-ord('0')]);

tt:=9;
for i:=length(s)-1 downto 1 do begin dec(tot[0],tt*i);tt:=tt*10;end;

end;

begin
assign(input,'count.in');
assign(output,'count.out');
reset(input);rewrite(output);

z[0]:=0;
for i:=1 to 13 do z[i]:=z[i-1]*10+f10(i-1);

readln(aa,bb);
aa:=aa-1;
str(aa,a);str(bb,b);
fillchar(tot,sizeof(tot),0);
for i:=length(a) downto 1 do
begin
if i<>1 then work1((ord(a[i])-ord('0'))*f10(length(a)-i))
        else work2((ord(a[i])-ord('0'))*f10(length(a)-i));
for j:=1 to i-1 do
inc(tot[ord(a[j])-ord('0')],(ord(a[i])-ord('0'))*f10(length(a)-i));
end;
tot2:=tot;

fillchar(tot,sizeof(tot),0);
for i:=length(b) downto 1 do
begin
if i<>1 then work1((ord(b[i])-ord('0'))*f10(length(b)-i))
        else work2((ord(b[i])-ord('0'))*f10(length(b)-i));
for j:=1 to i-1 do
inc(tot[ord(b[j])-ord('0')],(ord(b[i])-ord('0'))*f10(length(b)-i));
end;


for i:=0 to 8 do write(tot[i]-tot2[i],' ');writeln(tot[9]-tot2[9]);
close(input);close(output);
end.
