var
        l,r,len,i,j:longint;
        check:array[1..65536] of boolean;
        prime:array[1..10000] of longint;
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
        for i:=1 to 65536 do check[i]:=false;
        fo
end.
