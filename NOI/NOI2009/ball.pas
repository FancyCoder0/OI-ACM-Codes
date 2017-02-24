//非常巧妙的DP
//F[i1,j1,i2,j2]表示第一种操作方式X取到(i1,j1),第二种操作方式Y取到(i2,j2)时的“方案总数”
//因为一种可能的情况的次数^2=取两次的“方案总数”（(X,Y)的对数）

const P=1024523;
var n,m,i,j,k,l,i1,j1,i2:longint;
    a,b:array[1..600] of char;
    f:array[0..1,0..500,0..500] of longint;
begin
assign(input,'ball.in');
assign(output,'ball.out');
reset(input);rewrite(output);

     readln(n,m);
     for i:=1 to n do read(a[i]);readln;
     for i:=n+1 to 600 do a[i]:='!';
     for i:=1 to m do read(b[i]);readln;
     for i:=m+1 to 600 do b[i]:='@';

     f[0,0,0]:=1;
     for i1:=0 to n do
     begin
         for j1:=0 to m do
         for i2:=0 to n do
         f[(i1+1) mod 2,j1,i2]:=0;

         for j1:=0 to m do
         for i2:=0 to n do
         if f[i1 mod 2,j1,i2]>0 then
         begin
              if (i1<n)or(i2<n) then if a[i1+1]=a[i2+1] then
              f[(i1+1) mod 2,j1,i2+1]:=(f[(i1+1) mod 2,j1,i2+1]+f[i1 mod 2,j1,i2]) mod P;
              if a[i1+1]=b[(i1+j1-i2)+1] then
              f[(i1+1) mod 2,j1,i2]:=(f[(i1+1) mod 2,j1,i2]+f[i1 mod 2,j1,i2]) mod P;
              if b[j1+1]=a[i2+1] then
              f[i1 mod 2,j1+1,i2+1]:=(f[i1 mod 2,j1+1,i2+1]+f[i1 mod 2,j1,i2]) mod P;
              if (j1<m)or(i1+j1-i2<m) then if b[j1+1]=b[(i1+j1-i2)+1] then
              f[i1 mod 2,j1+1,i2]:=(f[i1 mod 2,j1+1,i2]+f[i1 mod 2,j1,i2]) mod P;
         end;
     end;
     writeln(f[n mod 2,m,n]);
close(input);close(output);
end.
