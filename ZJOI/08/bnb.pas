//贪心 O(nlogn)
//策略：我方A 他方B 
//Amin>Bmin Amin对Bmin else
//Amin<Bmin Amin对Bmax else
//Amax>Bmax Amax对Bmax else
//Amax<Bmax Amin对Bmax else
//Amax=Bmax Amin对Bmax

var n,i,j,k,l,r,rr,p,ans:longint;
    a,b,t:array[1..100000] of longint;
procedure sort(x,y:longint);
var i,j,mid,t:longint;
begin
i:=x;
j:=y;
mid:=a[(x+y) div 2];
repeat
while a[i]>mid do i:=i+1;
while a[j]<mid do j:=j-1;
if i<=j then
begin
t:=a[i];a[i]:=a[j];a[j]:=t;
i:=i+1;
j:=j-1;
end;
until i>j;
if i<y then sort(i,y);
if x<j then sort(x,j);
end;

procedure sort2(x,y:longint);
var i,j,mid,t:longint;
begin
i:=x;
j:=y;
mid:=b[(x+y) div 2];
repeat
while b[i]>mid do i:=i+1;
while b[j]<mid do j:=j-1;
if i<=j then
begin
t:=b[i];b[i]:=b[j];b[j]:=t;
i:=i+1;
j:=j-1;
end;
until i>j;
if i<y then sort2(i,y);
if x<j then sort2(x,j);
end;
function max(a,b:longint):longint;
begin
if a>b then exit(a) else exit(b);
end;
begin
assign(input,'bnb.in');
assign(output,'bnb.out');
reset(input);rewrite(output);

readln(n);
for i:=1 to n do read(a[i]);
for i:=1 to n do read(b[i]);
sort(1,n);
sort2(1,n);
l:=1;r:=n;i:=1;j:=n;ans:=0;
repeat
if a[r]>b[j] then begin ans:=ans+2;r:=r-1;j:=j-1;end
             else
if a[r]<b[j] then begin r:=r-1;i:=i+1;end
             else
if a[l]>b[i] then begin ans:=ans+2;l:=l+1;i:=i+1;end
             else
if a[l]<b[i] then begin r:=r-1;i:=i+1;end
             else
if a[r]<b[i] then begin r:=r-1;i:=i+1;end
             else begin ans:=ans+1;r:=r-1;i:=i+1;end;
until l>r;

write(ans,' ');

t:=a;a:=b;b:=t;

l:=1;r:=n;i:=1;j:=n;ans:=0;
repeat
if a[r]>b[j] then begin ans:=ans+2;r:=r-1;j:=j-1;end
             else
if a[r]<b[j] then begin r:=r-1;i:=i+1;end
             else
if a[l]>b[i] then begin ans:=ans+2;l:=l+1;i:=i+1;end
             else
if a[l]<b[i] then begin r:=r-1;i:=i+1;end
             else
if a[r]<b[i] then begin r:=r-1;i:=i+1;end
             else begin ans:=ans+1;r:=r-1;i:=i+1;end;
until l>r;

writeln(2*n-ans);
close(input);close(output);
end.







