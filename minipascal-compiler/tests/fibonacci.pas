program fibonacci;
var n, a, b, i, next: integer;
begin
  n := argi(1);
  if n <= 0 then
    writeln(0)
  else
  begin
    a := 0;
    b := 1;
    for i := 1 to n - 1 do
    begin
      next := a + b;
      a := b;
      b := next
    end;
    writeln(b)
  end
end.
