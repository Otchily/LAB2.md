program factor;
var n, d: integer;
begin
  n := argi(1);
  d := 2;
  while d * d <= n do
  begin
    while n mod d = 0 do
    begin
      write(d, ' ');
      n := n div d
    end;
    d := d + 1
  end;
  if n > 1 then
    writeln(n)
  else
    writeln
end.
