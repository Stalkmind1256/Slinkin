{$mode objfpc}
var a:array of string=
(
'0001010101001',
'0001010101001',
'0001010101001',
'0001010101001',
'0001010101001',
'1111010101001',
'0001000101001',
'0001010101001',
'0001010101001'
);



procedure paint(x,y:integer);
begin
 if (x<1)or(x>length(a[0]))or(y<0)or(y>=length(a))
	or(a[y,x]='1') then exit;
 a[y,x]:='1';
 paint(x+1,y);
 paint(x,y+1);
 paint(x-1,y);
 paint(x,y-1);
end; 

 var s:string;
BEGIN
 for s in a do writeln(s);
 paint(1,0);
 writeln('------------------------');
 for s in a do writeln(s);

END.

