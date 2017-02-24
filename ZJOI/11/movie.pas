type arr=array[0..1000] of longint;
var t,n,k,i,j,l,p:longint;
    s1,s2:arr;
procedure mul(var a:arr;t:longint);
var i:longint;
begin
        for i:=1 to a[0] do a[i]:=a[i]*t;
        for i:=1 to a[0]+10 do
        begin
                a[i+1]:=a[i+1]+a[i] div 10;
                a[i]:=a[i] mod 10;
                if (a[i]>0)and(i>a[0]) then a[0]:=i;
        end;
end;
function yushu(a:arr;t:longint):boolean;
var i,x:longint;
begin
     x:=0;
     for i:=a[0] downto 1 do
     begin
        x:=x*10+a[i];
        a[i]:=x div t;
        x:=x mod t;
     end;
     if x=0 then exit(true) else exit(false);
end;
procedure chu(var a:arr;t:longint);
var i,x:longint;
begin
     x:=0;
     for i:=a[0] downto 1 do
     begin
        x:=x*10+a[i];
        a[i]:=x div t;
        x:=x mod t;
     end;
     while (a[0]>1)and(a[a[0]]=0) do dec(a[0]);
end;


begin
assign(input,'movie.in');
assign(output,'movie.out');
reset(input);rewrite(output);
        readln(t);
        for l:=1 to t do
        begin
                readln(n,k);
                if k<n then writeln('0 1')
                       else
                begin
                p:=k+1-n;
                fillchar(s1,sizeof(s1),0);
                fillchar(s2,sizeof(s2),0);
                s1[0]:=1;s1[1]:=1;
                for i:=1 to n-1 do mul(s1,k+1);
                s2[0]:=1;s2[1]:=1;
                for i:=1 to n do mul(s2,k);

                i:=2;
                repeat
                if i>p then break;
                if (p mod i=0)and(yushu(s2,i)) then begin chu(s2,i);p:=p div i;end
                                               else i:=i+1;
                until false;
                mul(s1,p);

                for i:=s1[0] downto 1 do write(s1[i]);write(' ');
                for i:=s2[0] downto 1 do write(s2[i]);writeln;
                end;
        end;
close(input);close(output);
end.






