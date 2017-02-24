var
	n,k:longint;
function min(a,b:longint):longint;
begin
	if a<b then exit(a) else exit(b);
end;
begin
	assign(input,'function.in');
	assign(output,'function.out');
	reset(input);rewrite(output);
	readln(n,k);
	if n=1 then writeln(1)
	else
	writeln(2*min(k,n-k+1));
	close(input);close(output);
end.