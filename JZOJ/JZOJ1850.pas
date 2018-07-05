uses math;
var
        l,r,len,i,j,u,v,mx,mi,a,b,c,d:longint;
        check:array[1..65536] of boolean;
		pd:array[0..1000000] of boolean;
        prime:array[1..10000] of longint;
		zs:array[1..1000000] of longint;
begin
        readln(l,r);
        len:=0;
		for i:=2 to 65536 do
        begin
                if check[i]=false then
                begin
                    inc(len);
                    prime[len]:=i;
                end;
                j:=i+i;
                while j<=65536 do
                begin
                        check[j]:=true;
                        j:=j+i;
                end;
		end;
		for i:=1 to len do
		begin
			u:=max(l div prime[i], 1);
			v:=r div prime[i];
			for j:=u to v do
			begin
				if j=1 then continue;
				if j*prime[i]<l then continue;
				pd[j*prime[i]-l]:=true;
			end;
		end;
		len:=0;
		if l=1 then pd[0]:=true;
		for i:=0 to r-l do
		begin
			if pd[i]=false then
			begin
				inc(len);
				zs[len]:=i+l;
			end;
		end;
		for i:=2 to len do
		begin
			if mx=0 then
			begin
				mx:=zs[i]-zs[i-1];
				a:=zs[i-1];
				b:=zs[i];
			end else
			begin
				if zs[i]-zs[i-1]>mx then
				begin
					mx:=zs[i]-zs[i-1];
					a:=zs[i-1];
					b:=zs[i];
				end;
			end;
			if mi=0 then
			begin
				mi:=zs[i]-zs[i-1];
				c:=zs[i-1];
				d:=zs[i];
			end else
			begin
				if zs[i]-zs[i-1]<mi then
				begin
					mi:=zs[i]-zs[i-1];
					c:=zs[i-1];
					d:=zs[i];
				end;
			end;
		end;
		if len<2 then
		begin
			writeln('There are no adjacent primes.');
		end else
		begin
			writeln(c,',',d,' are closest, ',a,',',b,' are most distant.');
		end;
end.
