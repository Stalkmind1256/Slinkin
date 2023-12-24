Uses SysUtils;

{$H+}

Type ByteSet = Set Of Byte;

Var SByte, SByteTwo: ByteSet;
	Number, I, Value: Byte;
	Line: String;
	ByteArray: Array Of String;
	BytePtrOne, BytePtrTwo: PByte;


Function InSet(e: Byte; bset: ByteSet): Boolean;
Var BytePtr: PByte;
	ByteIndex, BitIndex: Byte;
Begin
	BytePtr := @bset;
	ByteIndex := e Div 8;
	BitIndex := e Mod 8;
	Inc(BytePtr, ByteIndex);
	InSet := (BytePtr^ And (1 Shl BitIndex)) <> 0;
End;


Function AddSet(b1set, b2set: ByteSet): ByteSet;
Var BytePtrOne, BytePtrTwo: PByte;
	I: Byte;
Begin
	BytePtrOne := @b1set;
	BytePtrTwo := @b2set;
	For I := 0 To SizeOf(ByteSet) - 1 Do
		BytePtrOne[i] := BytePtrOne[i] Or BytePtrTwo[i];
	AddSet := b1set;
End;


Function SubSet(b1set, b2set: ByteSet): ByteSet;
Var BytePtrOne, BytePtrTwo: PByte;
	I: Byte;
Begin
	BytePtrOne := @b1set;
	BytePtrTwo := @b2set;
	For I := 0 To SizeOf(ByteSet) - 1 Do
		BytePtrOne[i] := BytePtrOne[i] And Not BytePtrTwo[i];
	SubSet := b1set;
End;


Function MulSet(b1set, b2set: ByteSet): ByteSet;
Var BytePtrOne, BytePtrTwo: PByte;
	I: Byte;
Begin
	BytePtrOne := @b1set;
	BytePtrTwo := @b2set;
	For I := 0 To SizeOf(ByteSet) - 1 Do
		BytePtrOne[i] := BytePtrOne[i] And BytePtrTwo[i];
	MulSet := b1set;
End;


Function IncludeSet(e: Byte; bset: ByteSet): ByteSet;
Var BytePtr: PByte;
	ByteIndex, BitIndex: Byte;
Begin
	BytePtr := @bset;
	ByteIndex := e Div 8;
	BitIndex := e Mod 8;
	Inc(BytePtr, ByteIndex);
	BytePtr^ := BytePtr^ Or (1 Shl BitIndex);
	IncludeSet := bset;
End;


Function ExcludeSet(e: Byte; bset: ByteSet): ByteSet;
Var BytePtr: PByte;
	ByteIndex, BitIndex: Byte;
Begin
	BytePtr := @bset;
	ByteIndex := e Div 8;
	BitIndex := e Mod 8;
	Inc(BytePtr, ByteIndex);
	BytePtr^ := BytePtr^ And Not (1 Shl BitIndex);
	ExcludeSet := bset;
End;


Begin
  WriteLn('1 - Создать множество');
  WriteLn('2 - Проверить число во множестве');
  WriteLn('3 - Добавить множество во множество');
  WriteLn('4 - Удалить множество из множества');
  WriteLn('5 - Пересечь множества');
  WriteLn('6 - Добавить число во множество');
  WriteLn('7 - Удалить число из множества');
  WriteLn('8 - Вывести множество');
  WriteLn('9 - Выйти из программы');
  ReadLn(Number);
  
  While Number <> 9 do
  begin
    BytePtrTwo := @SByteTwo;
    for I := 0 to SizeOf(ByteSet) - 1 do
      BytePtrTwo[I] := 0;
    
    case Number Of
      1:begin
        Write('Числа через пробел: ');
        ReadLn(Line);
        ByteArray := Line.Split(' ');
        BytePtrOne := @SByte;
        for I := 0 to SizeOf(ByteSet) - 1 do
			BytePtrOne[I] := 0;
        if Length(ByteArray) <= 256 then
          for I := 0 to Length(ByteArray) - 1 do
            SByte := IncludeSet(Byte(StrToInt(ByteArray[I])), SByte)
        else
          for I := 0 to 255 do
            SByte := IncludeSet(Byte(StrToInt(ByteArray[I])), SByte);
      end;
      
      2:
      begin
        Write('Проверяемое число: ');
        ReadLn(Value);
        if InSet(Value, SByte) then
          WriteLn('Элемент принадлежит множеству')
        else
          WriteLn('Элемент не принадлежит множеству');
      end;
      
      3:
      begin
        Write('Числа через пробел во втором множестве: ');
        ReadLn(Line);
        ByteArray := Line.Split(' ');
        if Length(ByteArray) <= 256 then
          for I := 0 to Length(ByteArray) - 1 do
            SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo)
        else
          for I := 0 to 255 do
            SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo);
        SByte := AddSet(SByte, SByteTwo);
      end;
      
      4:
      begin
        Write('Числа через пробел во втором множестве: ');
        ReadLn(Line);
        ByteArray := Line.Split(' ');
        if Length(ByteArray) <= 256 then
          for I := 0 To Length(ByteArray) - 1 do
            SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo)
        else
          for I := 0 to 255 do
            SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo);
        SByte := SubSet(SByte, SByteTwo);
      end;
      
      5:
      begin
        Write('Числа через пробел во втором множестве: ');
        ReadLn(Line);
        ByteArray := Line.Split(' ');
        if Length(ByteArray) <= 256 then
          for I := 0 to Length(ByteArray) - 1 do
            SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo)
        else
          for I := 0 to 255 do
            SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo);
        SByte := MulSet(SByte, SByteTwo);
      end;
      
      6:
      begin
        Write('Добавляемое число: ');
        ReadLn(Value);
        SByte := IncludeSet(Value, SByte);
      end;
      
      7:
      begin
        Write('Удаляемое число: ');
        ReadLn(Value);
        SByte := ExcludeSet(Value, SByte);
      end;
      
      8:
      begin
        Write('Множество: { ');
        for I := 0 to 255 do
          if InSet(I, SByte) then
            Write(I, ' ');
        WriteLn('}');
      end;
      
      else
        WriteLn('Число не соответствует диапазону');
    end;
    
    WriteLn;
    WriteLn('1 - Создать множество');
    WriteLn('2 - Проверить число во множестве');
    WriteLn('3 - Добавить множество во множество');
    WriteLn('4 - Удалить множество из множества');
    WriteLn('5 - Пересечь множества');
    WriteLn('6 - Добавить число во множество');
    WriteLn('7 - Удалить число из множества');
    WriteLn('8 - Вывести множество');
    WriteLn('9 - Выйти из программы');
    ReadLn(Number);
  end;
  
  WriteLn('Выход');
End.
