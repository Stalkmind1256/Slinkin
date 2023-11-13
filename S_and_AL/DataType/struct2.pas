program DataType;

uses
  SysUtils;

var
  inputString: string;
  i: integer;
  byteValue: array[0..1] of Byte;
  SI: Shortint;
  SmI: SmallInt;
  LI:Longint;
  LW:Longword;
  B:Byte;
  randomNumber:byte;
  W:Word;
  Card:Cardinal;
  Bool:Boolean;
  randomChar:Char;
  QW:QWord;
  INT_64:Int64;

begin
  Randomize; 
  Write('Enter data type: ');
  Readln(inputString);
  
  if (LowerCase(inputString) = 'shortint') then
begin
    writeln('Type being tested: Shortint ');
    writeln('Lower line: ', Low(Shortint));
    writeln('Upper line: ', High(Shortint));
    writeln('Byte: ', SizeOf(Shortint));
    SI := Random(256);
    writeln('Random Value: ', SI);
    writeln('Succ Value: ', Succ(SI));
    writeln('Pred Value: ', Pred(SI));
    if (SI = High(Shortint)) or (SI = Low(Shortint)) then
    begin
      writeln('Overflow');
    end;
end
  else if (LowerCase(inputString) = 'smallint') then
  
begin
    writeln('Type being tested: SmallInt ');
    writeln('Lower line: ', Low(SmallInt));
    writeln('Upper line: ', High(SmallInt));
    writeln('Byte: ', SizeOf(SmallInt));
    
    for i := 0 to SizeOf(SmallInt) - 1 do
    begin
      byteValue[i] := Random(256);
	end;
    
    SmI := (SmallInt(byteValue[1]) shl 8) or byteValue[0];
    writeln('Random Value: ', SmI);
    writeln('Succ Value: ', Succ(SmI));
    writeln('Pred Value: ', Pred(SmI));
    
    for i := 0 to SizeOf(SmallInt) - 1 do
    begin
      Write(byteValue[i], ' ');
    end;
    Writeln();
    
    if (SmI = High(SmallInt)) or (SmI = Low(SmallInt)) then
    begin
      writeln('Overflow');
    end;
end
	else if (LowerCase(inputString) = 'longint') then
	
begin
  writeln('Type being tested: Longint ');
  writeln('Lower line: ', Low(Longint));
  writeln('Upper line: ', High(Longint));
  writeln('Byte: ', Sizeof(Longint));

  for i := 0 to sizeof(Longint) - 1 do
  begin
    byteValue[i] := Random(256);
  end;

  LI := 0;
  for i := sizeof(Longint) - 1 downto 0 do
  begin
    LI := (LI shl 8) or byteValue[i];
  end;
  
  writeln('Random Value: ', LI);
  writeln('Succ Value: ', Succ(LI));
  writeln('Pred Value: ', Pred(LI));

  for i := 0 to sizeof(Longint) - 1 do
  begin
    Write(byteValue[i], ' ');
  end;

  Writeln();

  if (LI = High(Longint)) or (LI = Low(Longint)) then
  begin
    write('Overflow');
  end;
end
	else if (LowerCase(inputString) = 'longword') then
	
begin
  writeln('Type being tested: Longword ');
  writeln('Lower line: ', Low(Longword));
  writeln('Upper line: ', High(Longword));
  writeln('Byte: ', Sizeof(Longword));

  for i := 0 to SizeOf(Longword) - 1 do
  begin
    byteValue[i] := Random(256);
  end;

  LW := 0;
  for i := SizeOf(Longword) - 1 downto 0 do
  begin
    LW := (LW shl 8) or byteValue[i];
  end;

  writeln('Random Value: ', LW);
  writeln('Succ Value: ', Succ(LW));
  writeln('Pred Value: ', Pred(LW));

  for i := 0 to SizeOf(Longword) - 1 do
  begin
    Write(byteValue[i], ' ');
  end;

  Writeln();

  if (LW = High(Longword)) or (LW = Low(Longword)) then
  begin
    writeln('Overflow');
  end;
end
	else if (LowerCase(inputString) = 'byte') then
	
begin
  writeln('Type being tested: Byte ');
  writeln('Lower line: ', Low(Byte));
  writeln('Upper line: ', High(Byte));
  writeln('Byte: ', Sizeof(Byte));

  B := Random(256);
  writeln('Random Value: ', B);
  writeln('Succ Value: ', Succ(B));
  writeln('Pred Value: ', Pred(B));

  byteValue := PByte(@B);
  for i := 0 to Sizeof(B) - 1 do
  begin
    Writeln(byteValue[i]);
  end;

  if (B = High(Byte)) or (B = Low(Byte)) then
  begin
    writeln('Overflow');
  end;
end
	else if (LowerCase(inputString) = 'word') then
begin
	writeln('Type being tested: Word ');
	writeln('Lower line: ', Low(Word));
	writeln('Upper line: ', High(Word));
	writeln('Byte: ', Sizeof(Word));
	for i := 0 to SizeOf(Word) - 1 do
		begin
			byteValue[i] := Random(256);
		end;
		
  W := 0;
  for i := sizeof(Word) - 1 downto 0 do
  begin
    W := (W shl 8) or byteValue[i];
  end;
		writeln('Random Value: ', W);
		writeln('Succ Value: ', Succ(W));
		writeln('Pred Value: ', Pred(W));
		
	for i := 0 to SizeOf(Word) - 1 do
  begin
    Write(byteValue[i], ' ');
  end;
	writeln();
	if (W= High(Byte)) or (W = Low(Byte)) then
  begin
    writeln('Overflow');
  end;
	
  Writeln();	 
end
	else if (LowerCase(inputString) = 'cardinal') then
	
begin
	writeln('Type being tested: Word ');
	writeln('Lower line: ', Low(Cardinal));
	writeln('Upper line: ', High(Cardinal));
	writeln('Byte: ', Sizeof(Cardinal));
	for i := 0 to SizeOf(Cardinal) - 1 do
		begin
			byteValue[i] := Random(256);
		end;
		
  Card := 0;
  for i := sizeof(Cardinal) - 1 downto 0 do
  begin
    Card := (Card shl 8) or byteValue[i];
  end;
		writeln('Random Value: ', Card);
		writeln('Succ Value: ', Succ(Card));
		writeln('Pred Value: ', Pred(Card));
		
	for i := 0 to SizeOf(Cardinal) - 1 do
  begin
    Write(byteValue[i], ' ');
  end;
	writeln();
	if (Card= High(Cardinal)) or (Card = Low(Cardinal)) then
  begin
    writeln('Overflow');
  end;
end
	else if (LowerCase(inputString) = 'boolean') then
		begin
		  writeln('Type being tested: Boolean');
		  writeln('Lower line: ', Low(Boolean));
		  writeln('Upper line: ', High(Boolean));
		  writeln('Byte: ', Sizeof(Boolean));
		  
		  Bool:= Boolean(Random(2));
		  writeln('Random Value: ', Boolean(Bool));
		  writeln('Succ Value: ', Succ(Bool));
		  writeln('Pred Value: ', Pred(Bool));
		
		 byteValue := PByte(@Bool);
		  for i := 0 to Sizeof(Bool) - 1 do
			Writeln(byteValue[i]);
		
		 if Bool = (Low(Boolean) or High(Boolean)) then
			begin
				Writeln('Overflow');
			end;
		  
	end	
		else if (LowerCase(inputString) = 'char') then
	begin
	  begin
		  Writeln('Type being tested: Char');
		  Writeln('Lower line: ', Ord(Low(Char)));
		  Writeln('Upper line: ', Ord(High(Char)));
		  Writeln('Byte: ', Sizeof(Char));
		  
		  randomNumber := Random(256);
		  randomChar:=chr(randomNumber);

		  Writeln('Random Value: ', ord(randomChar));
		  Writeln('Succ Value: ', Ord(Succ(randomChar)));
		  Writeln('Pred Value: ', Ord(Pred(randomChar)));

		  if randomChar = High(Char) then
			Writeln('Overflow');

		  if randomChar = Low(Char) then
			Writeln('Underflow');

		  byteValue := PByte(@randomChar);
		  
		  for i := 0 to Sizeof(randomChar) - 1 do
			Writeln(byteValue[i]);
		end;
	end
		else if (lowercase(inputString) = 'qword') then
			begin
		  writeln('Type being tested: Word ');
		  writeln('Lower line: ', Low(QWord));
		  writeln('Upper line: ', High(QWord));
		  writeln('Byte: ', Sizeof(QWord));
		  for i := 0 to SizeOf(QWord) - 1 do
			  begin
				byteValue[i] := Random(256);
			  end;
		
		  QW := 0;
		  for i := sizeof(QWord) - 1 downto 0 do
		  begin
			QW := (QW shl 8) or byteValue[i];
		  end;
				writeln('Random Value: ', QW);
				writeln('Succ Value: ', Succ(QW));
				writeln('Pred Value: ', Pred(QW));
				
			for i := 0 to SizeOf(QWord) - 1 do
		  begin
			Write(byteValue[i], ' ');
		  end;
			writeln();
			if (QW= High(Byte)) or (QW = Low(Byte)) then
		  begin
			writeln('Overflow');
		  end;
	end
		else if (lowercase(inputString) = 'int64') then
	begin
			writeln('Type being tested: Word ');
		  writeln('Lower line: ', Low(Int64));
		  writeln('Upper line: ', High(Int64));
		  writeln('Byte: ', Sizeof(Int64));
		  for i := 0 to SizeOf(Int64) - 1 do
			  begin
				byteValue[i] := Random(256);
			  end;
		
		  INT_64 := 0;
		  for i := sizeof(Int64) - 1 downto 0 do
		  begin
			INT_64 := (INT_64 shl 8) or byteValue[i];
		  end;
				writeln('Random Value: ', INT_64);
				writeln('Succ Value: ', Succ(INT_64));
				writeln('Pred Value: ', Pred(INT_64));
				
			for i := 0 to SizeOf(Int64) - 1 do
		  begin
			Write(byteValue[i], ' ');
		  end;
			writeln();
	if (INT_64 = High(Int64)) or (INT_64 = Low(Int64)) then
	begin
		writeln('Overflow');
	end;
end
	else 
		writeln('Error');
end.
