PROGRAM PR15;

var 
  inputstring: string;
  i:integer;
  byteValue:PByte;
  randomSI: Shortint;
  randomSmI:SmallInt;
  randomLI:Longint;
  randomLw:Longword;
  randomByte:Byte;
  randomW:Word;
  randomCard:Cardinal;
 // randomCh:Char;
  randBool:Boolean;
  
BEGIN
  randomize;
  WRITE('Enter data type:');
  readln(inputstring);

  if (inputString = 'Shortint') then
  begin
    writeln('Type being tested: Shortint ');
    writeln('Lower line: ', Low(Shortint));
    writeln('Upper line: ', High(Shortint));
    writeln('Byte: ', Sizeof(Shortint));
    randomSI := Random(256) - Low(Shortint);
    writeln('Random Value: ', randomSI);
    writeln('Succ Value: ', Succ(randomSI));
    writeln('Pred Value: ', Pred(randomSI));
    if randomSI = High(Shortint) then
      Writeln('overflow');
    if randomSI = Low(Shortint) then
      Writeln('overflow');
    byteValue := PByte(@randomSI);
    for i:= 0 to Sizeof(Shortint) - 1 do
    Writeln('Contents of RAM: ',bytevalue[i],' ');
  end
  else if (inputString = 'SmallInt') then
	  begin
		writeln('Type being tested: SmallInt ');
		writeln('Lower line: ', Low(SmallInt));
		writeln('Upper line: ', High(SmallInt));
		writeln('Byte: ', Sizeof(SmallInt));
		randomSmI := Random(65536) - Low(SmallInt);
		writeln('Random Value: ', randomSmI);
		writeln('Succ Value: ', Succ(randomSmI));
		writeln('Pred Value: ', Pred(randomSmI));
		if randomSmI = High(SmallInt) then
		  Writeln('overflow');
		if randomSmI = Low(SmallInt) then
		  Writeln('overflow');
		byteValue := PByte(@randomSmI);
		for i:= 0 to Sizeof(randomSmI) - 1 do
		begin
		Writeln(bytevalue[i]);
		end;
  end
  else if(inputString ='Longint') then
	begin
		writeln('Type being tested: Longint ');
		writeln('Lower line: ', Low(Longint));
		writeln('Upper line: ', High(Longint));
		writeln('Byte: ', Sizeof(Longint));
		randomLI := Random(2147483647) - Low(Longint) ;
		writeln('Random Value: ', randomLI);
		writeln('Succ Value: ', Succ(randomLI));
		writeln('Pred Value: ', Pred(randomLI));
		if randomLI = High(Longint) then
		  Writeln('overflow');
		if randomLI = Low(Longint) then
		  Writeln('overflow');
		byteValue := PByte(@randomLI);
		for i:= 0 to Sizeof(randomLI) - 1 do
		begin
		Writeln(bytevalue[i]);
		end;
	end
	else if(inputString ='Longword') then 
		begin
		writeln('Type being tested: Longword ');
		writeln('Lower line: ', Low(Longword));
		writeln('Upper line: ', High(Longword));
		writeln('Byte: ', Sizeof(Longword));
		randomLw := Random(4294967296);
		writeln('Random Value: ', randomLw);
		writeln('Succ Value: ', Succ(randomLw));
		writeln('Pred Value: ', Pred(randomLw));
		if randomLw = High(Longword) then
		  Writeln('overflow');
		if randomLw = Low(Longword) then
		  Writeln('overflow');
		byteValue := PByte(@randomLw);
		for i:= 0 to Sizeof(randomLw) - 1 do
		begin
		Writeln(bytevalue[i]);
		end;
	end
	else if (inputString = 'Byte') then
		begin
		  writeln('Type being tested: Byte ');
		  writeln('Lower line: ', Low(Byte));
		  writeln('Upper line: ', High(Byte));
		  writeln('Byte: ', Sizeof(Byte));
		  randomByte := Random(256);
		  writeln('Random Value: ', randomByte);
		  writeln('Succ Value: ', Succ(randomByte));
		  writeln('Pred Value: ', Pred(randomByte));
		  if randomByte = High(Byte) then
			Writeln('overflow');
		  if randomByte = Low(Byte) then
			Writeln('overflow');
		  byteValue := PByte(@randomByte);
		  for i := 0 to Sizeof(randomByte) - 1 do
		  begin
			Writeln(byteValue[i]);
		  end;
		end
	else if (inputString = 'Word') then
		begin
		  writeln('Type being tested: Word ');
		  writeln('Lower line: ', Low(Word));
		  writeln('Upper line: ', High(Word));
		  writeln('Byte: ', Sizeof(Word));
		  randomW := Random(65536);
		  writeln('Random Value: ', randomW);
		  writeln('Succ Value: ', Succ(randomW));
		  writeln('Pred Value: ', Pred(randomW));
		  if randomW = High(Word) then
			Writeln('overflow');
		  if randomW = Low(Word) then
			Writeln('overflow');
		  byteValue := PByte(@randomW);
		  for i := 0 to Sizeof(randomW) - 1 do
		  begin
			Writeln(byteValue[i]);
		  end;
		end
	else if (inputString = 'Cardinal') then
		begin
		  writeln('Type being tested: Cardinal');
		  writeln('Lower line: ', Low(Cardinal));
		  writeln('Upper line: ', High(Cardinal));
		  writeln('Byte: ', Sizeof(Cardinal));
		  randomCard := Random(4294967296);
		  writeln('Random Value: ', randomCard);
		  writeln('Succ Value: ', Succ(randomCard));
		  writeln('Pred Value: ', Pred(randomCard));
		  if randomCard = High(Cardinal) then
			Writeln('overflow');
		  if randomCard = Low(Cardinal) then
			Writeln('overflow');
		  byteValue := PByte(@randomCard);
		  for i := 0 to Sizeof(randomCard) - 1 do
		  begin
			Writeln(byteValue[i]);
		  end;
		end
	else if (inputString = 'Boolean') then
		begin
		  writeln('Type being tested: Boolean');
		  writeln('Lower line: ', Low(Boolean));
		  writeln('Upper line: ', High(Boolean));
		  writeln('Byte: ', Sizeof(Boolean));
		  
		  randBool := Boolean(Random(2));
		  writeln('Random Value: ', Boolean(randBool));
		  writeln('Succ Value: ', Succ(randBool));
		  writeln('Pred Value: ', Pred(randBool));
		  
		  if randBool = High(Boolean) then
			Writeln('Overflow');
		  if randBool = Low(Boolean) then
			Writeln('Overflow');
		  if randBool = (Low(Boolean) and High(Boolean)) then
			Writeln('Overflow');
		  
		  byteValue := PByte(@randBool);
		  for i := 0 to Sizeof(randBool) - 1 do
			Writeln(byteValue[i]);
		end
	
	
	
	
	
	{else if (inputString = 'Char') then
		begin
		  writeln('Type being tested: Char');
		  writeln('Lower line: ', ord(Low(Char)));
		  writeln('Upper line: ', ord(High(Char)));
		  writeln('Byte: ', Sizeof(Char));
		  randomCh := Random(26) + 65;
		  randomChar := Chr(randomCh);
		  
		  writeln('Random Value: ', randomCh);
		  writeln('Succ Value: ', ord(Succ(randomCh)));
		  writeln('Pred Value: ', Pred(randomCh));
		  
		  if randomCh = High(Char) then
			Writeln('Overflow');
		  if randomCh = Low(Char) then
			Writeln('Underflow');
		  
		  byteValue := PByte(@randomChar);
		  for i := 0 to Sizeof(randomChar) - 1 do
			writeln(byteValue[i]);
		end.
}
	
	
	
  {else if (inputString = 'Int64') then
begin
  writeln('Type being tested: Int64 ');
  writeln('Lower line: ', Low(Int64));
  writeln('Upper line: ', High(Int64));
  writeln('Byte: ', Sizeof(Int64));
  randomI64 := Random(Int64.MaxValue - Int64.MinValue) + Int64.MinValue;
  writeln('Random Value: ', randomI64);
  writeln('Succ Value: ', Succ(randomI64));
  writeln('Pred Value: ', Pred(randomI64));
  if randomI64 = High(Int64) then
    Writeln('overflow');
  if randomI64 = Low(Int64) then
    Writeln('overflow');
  byteValue := PByte(@randomI64);
  for i := 0 to Sizeof(randomI64) - 1 do
  begin
    Writeln(byteValue[i]);
  end;
end
* }
END.
