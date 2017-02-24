//«…√Óµƒƒ£ƒ‚Ã‚
//O(n^2)
var n,i,j,k,l,p:longint;ttt:boolean;
    a,b,c:array[1..20000] of longint;
    pd:array[0..20000] of boolean;
    dd:array[0..20000,0..2] of longint;
    print:array[1..20000] of longint;
procedure search(i,j:longint);
begin
if print[i]<>-1 then exit;
if j=b[i] then
begin
print[i]:=b[i];pd[b[i]]:=true;
if dd[c[i],1]<>i then search(dd[c[i],1],c[i])
                      else search(dd[c[i],2],c[i]);
end
else
begin
print[i]:=c[i];pd[c[i]]:=true;
if dd[b[i],1]<>i then search(dd[b[i],1],b[i])
                       else search(dd[b[i],2],b[i]);
end;
end;

begin
assign(input,'transform.in');
assign(output,'transform.out');
reset(input);rewrite(output);
readln(n);
for i:=1 to n do read(a[i]);readln;
for i:=1 to n do begin b[i]:=((i-1)+a[i]) mod n;
                                  c[i]:=((i-1)-a[i]+n) mod n;end;
fillchar(print,sizeof(print),255);
fillchar(pd,sizeof(pd),false);
repeat
ttt:=true;
fillchar(dd,sizeof(dd),0);
for i:=1 to n do
if print[i]=-1 then
begin if dd[b[i],0]<=1 then begin  inc(dd[b[i],0]);dd[b[i],dd[b[i],0]]:=i;end;
         if dd[c[i],0]<=1 then begin  inc(dd[c[i],0]);dd[c[i],dd[c[i],0]]:=i;end;
end;
for i:=0 to n-1 do if (dd[i,0]=0)and(not pd[i]) then begin writeln('No Answer');close(input);close(output);halt;end;
for i:=0 to n-1 do
if (dd[i,0]=1)and(print[dd[i,1]]=-1) then begin print[dd[i,1]]:=i;pd[i]:=true;ttt:=false;end;
until ttt;
for i:=1 to n do
if print[i]=-1 then begin if b[i]<c[i] then search(i,b[i]) else search(i,c[i]);
                           end;
write(print[1]);for i:=2 to n do write(' ',print[i]);writeln;

close(input);close(output);
end.
