Program struct1;

uses
  SysUtils;

var
    //bytevalue: array of byte;
    i, datasize: byte;
    datatype: string;
    randomshi: Shortint;
    randomsmi: smallint;
    randomli: Longint;
    randomlword: longword;
    randomi64: int64;
    randombyte: byte;
    randomword: Word;
    randomcard: Cardinal;
    randomqword: QWord;
    randomchar: Char;
    randombool: Boolean;
    
    
begin
    randomize;
    Write('Enter data type: ');
    Readln(datatype);
    Writeln('Type being tested:', datatype);
    
    if (LowerCase(datatype )) = 'shortint' then 
begin
        datasize := sizeof(Shortint);
        Writeln('Lower Line: ', low(Shortint));
        Writeln('Upper Line: ', high(Shortint));
        Writeln('Byte: ', datasize);
        randomshi := 0;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randomshi := (randomshi shl 8) or random(256);
        Writeln('Random Value: ', randomshi);
        if low(Shortint)=randomshi then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randomshi));
        if high(Shortint)=randomshi then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randomshi));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randomshi)[i],' '); 
        Writeln;
end
    else if (LowerCase(datatype )) = 'smallint' then 
begin
        datasize := SizeOf(SmallInt);
        Writeln('Lower Line: ', low(Shortint));
        Writeln('Upper Line: ', high(Shortint));
        Writeln('Byte: ', datasize);
        randomsmi := 0;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randomsmi := (randomsmi shl 8) or random(256);
        Writeln('Random Value: ', randomsmi);
       	if low(Smallint)=randomsmi then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randomsmi));
        if high(Smallint)=randomsmi then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randomsmi));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randomsmi)[i],' '); 
        Writeln;
end 
    else if (LowerCase(datatype )) ='longint' then 
begin
        datasize := SizeOf(Longint);
        Writeln('Lower Line: ', low(Longint));
        Writeln('Upper Line: ', high(Longint));
        Writeln('Byte: ', datasize);
        randomli := 0;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randomli := (randomli shl 8) or random(256);
        Writeln('Random Value: ', randomli);
      	if low(Longint)=randomli then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randomli));
        if high(Longint)=randomli then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randomli));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randomli)[i],' '); 
        Writeln;
end
    else if (LowerCase(datatype )) = 'longword' then 
begin
        datasize := SizeOf(Longword);
        Writeln('Lower Line: ', low(Longword));
        Writeln('Upper Line: ', high(Longword));
        Writeln('Byte: ', datasize);
        randomlword:=0;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randomlword := (randomlword shl 8) or random(256);
        Writeln('Random Value: ', randomlword);
       	if low(Longword)=randomlword then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randomlword));
        if high(Longword)=randomlword then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randomlword));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randomlword)[i],' '); 
        Writeln;
end
    else if (LowerCase(datatype )) = 'int64' then 
begin
        datasize := sizeof(Int64);
        Writeln('Lower Line: ', low(Int64));
        Writeln('Upper Line: ', high(Int64));
        Writeln('Byte: ', datasize);
        randomi64 := 0;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randomi64 := (randomi64 shl 8) or random(256);
        Writeln('Random Value: ', randomi64);
        if low(Int64)=randomi64 then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randomi64));
        if high(Int64)=randomi64 then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randomi64));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randomi64)[i],' '); 
        Writeln;
end
    else if (LowerCase(datatype )) = 'byte' then 
begin
        datasize := sizeof(Byte);
        Writeln('Lower Line: ', low(Byte));
        Writeln('Upper Line: ', high(Byte));
        Writeln('Byte: ', datasize);
        randombyte := 0;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randombyte := (randombyte shl 8) or random(256);
        Writeln('Random Value: ', randombyte);
        if low(Byte)=randombyte then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randombyte));
        if high(Byte)=randombyte then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randombyte));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randombyte)[i],' '); 
        Writeln;
end
    else if (LowerCase(datatype )) = 'word' then 
begin
        datasize := sizeof(Word);
        Writeln('Lower Line: ', low(Word));
        Writeln('Upper Line: ', high(Word));
        Writeln('Byte: ', datasize);
        randomword := 0;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randomword := (randomword shl 8) or random(256);
        Writeln('Random Value: ', randomword);
        if low(Word)=randomword then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randomword));
        if high(Word)=randomword then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randomword));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randomword)[i],' '); 
        Writeln;
end
    else if (LowerCase(datatype )) = 'cardinal' then 
begin
        datasize := sizeof(Cardinal);
        Writeln('Lower Line: ', low(Cardinal));
        Writeln('Upper Line: ', high(Cardinal));
        Writeln('Byte: ', datasize);
        randomcard := 0;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randomcard := (randomcard shl 8) or  random(256);
        Writeln('Random Value: ', randomcard);
        if low(Cardinal)=randomcard then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randomcard));
        if high(Cardinal)=randomcard then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randomcard));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randomcard)[i],' '); 
        Writeln;
end
    else if (LowerCase(datatype )) = 'qword' then 
begin
        datasize := sizeof(QWord);
        Writeln('Lower Line: ', low(QWord));
        Writeln('Upper Line: ', high(QWord));
        Writeln('Byte: ', datasize);
        randomqword := 0;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randomqword := (randomqword shl 8) or random(256);
        Writeln('Random Value: ', randomqword);
        if low(QWord)=randomqword then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randomqword));
        if high(QWord)=randomqword then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randomqword));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randomqword)[i],' '); 
        Writeln;
end
    else if (LowerCase(datatype )) = 'char' then 
begin
        datasize := sizeof(Char);
        Writeln('Lower Line #: ', ord(low(Char)));
        Writeln('Upper Line #: ', ord(high(Char)));
        Writeln('Byte: ', datasize);
        randomchar := Chr(0);
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
        for i := datasize-1 downto 0 do randomchar := Chr((ord(randomchar) shl 8) or random(256));
        Writeln('Random Value: #', ord(randomchar));
        if ord(low(Char))=ord(randomchar) then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: #', ord(pred(randomchar)));
        if ord(high(Char))=ord(randomchar) then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: #', ord(succ(randomchar)));
        Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randomchar)[i],' '); 
        Writeln;
end
   else if (LowerCase(datatype )) = 'boolean' then 
begin
        datasize := sizeof(Boolean);
        Writeln('Lower Line: ', low(Boolean));
        Writeln('Upper Line: ', high(Boolean));
        Writeln('Byte: ', datasize);
        randombool := False;
        //SetLength(bytevalue,datasize);
        //for i := 0 to datasize-1 do bytevalue[i] := random(256);
		randombool:=boolean(random(2));
        Writeln('Random Value: ', randombool);
        if low(Boolean)=randombool then Writeln('Pred Value: overflow') 
			else Writeln('Pred Value: ', pred(randombool));
        if high(Boolean)=randombool then Writeln('Succ Value: overflow') 
			else Writeln('Succ Value: ', succ(randombool));
       Write('Contents of RAM: ');
        for i := 0 to datasize-1 do write(PByte(@randombool)[i],' '); 
        Writeln;
end
    else begin
        Writeln('Data type not found');
    end;
end.

