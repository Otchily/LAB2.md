program isprime;
var n, i: integer;
var prime: boolean;
begin
  n := argi(1);
  if n < 2 then
    prime := false
  else
  begin
    prime := true;
    i := 2;
    while i * i <= n do
    begin
      if n mod i = 0 then
      begin
        prime := false;
        i := n
      end;
      i := i + 1
    end
  end;
  writeln(prime)
end.
