program pidigits;
var n, i, scale, terms, sign, denom, piScaled, termValue, intPart, fracPart, tmp: integer;
begin
  n := argi(1);
  if n < 0 then
    n := 0;
  if n > 9 then
    n := 9;

  scale := 1;
  for i := 1 to n do
    scale := scale * 10;

  piScaled := 3 * scale;
  sign := 1;
  denom := 2;
  terms := 3000;

  for i := 1 to terms do
  begin
    termValue := (4 * scale) div (denom * (denom + 1) * (denom + 2));
    if sign = 1 then
      piScaled := piScaled + termValue
    else
      piScaled := piScaled - termValue;
    sign := 0 - sign;
    denom := denom + 2
  end;

  intPart := piScaled div scale;
  fracPart := piScaled mod scale;
  write(intPart, '.');
  tmp := scale div 10;
  while tmp > 0 do
  begin
    if fracPart < tmp then
      write(0);
    tmp := tmp div 10
  end;
  writeln(fracPart)
end.
