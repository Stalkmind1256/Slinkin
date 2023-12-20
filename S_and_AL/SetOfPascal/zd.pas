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
	While Number <> 9 Do
	Begin
		BytePtrTwo := @SByteTwo;
		For I := 0 To SizeOf(ByteSet) - 1 Do
			BytePtrTwo[I] := 0;
		If Number = 1 Then
		Begin
			Write('Числа через пробел: ');
			ReadLn(Line);
			ByteArray := Line.Split(' ');
			BytePtrOne := @SByte;
			For I := 0 To SizeOf(ByteSet) - 1 Do
				BytePtrOne[I] := 0;
			If Length(ByteArray) <= 256 Then
				For I := 0 To Length(ByteArray) - 1 Do
					SByte := IncludeSet(Byte(StrToInt(ByteArray[I])), SByte)
			Else
				For I := 0 To 255 Do
					SByte := IncludeSet(Byte(StrToInt(ByteArray[I])), SByte);
		End
		ELse If Number = 2 Then
		Begin
			Write('Проверяемое число: ');
			ReadLn(Value);
			If InSet(Value, SByte) Then
				WriteLn('Элемент принадлежит множеству')
			Else
				WriteLn('Элемент не принадлежит множеству');
		End
		Else If Number = 3 Then
		Begin
			Write('Числа через пробел во втором множестве: ');
			ReadLn(Line);
			ByteArray := Line.Split(' ');
			If Length(ByteArray) <= 256 Then
				For I := 0 To Length(ByteArray) - 1 Do
					SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo)
			Else
				For I := 0 To 255 Do
					SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo);
			SByte := AddSet(SByte, SByteTwo);
		End
		Else If Number = 4 Then
		Begin
			Write('Числа через пробел во втором множестве: ');
			ReadLn(Line);
			ByteArray := Line.Split(' ');
			If Length(ByteArray) <= 256 Then
				For I := 0 To Length(ByteArray) - 1 Do
					SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo)
			Else
				For I := 0 To 255 Do
					SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo);
			SByte := SubSet(SByte, SByteTwo);
		End
		Else If Number = 5 Then
		Begin
			Write('Числа через пробел во втором множестве: ');
			ReadLn(Line);
			ByteArray := Line.Split(' ');
			If Length(ByteArray) <= 256 Then
				For I := 0 To Length(ByteArray) - 1 Do
					SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo)
			Else
				For I := 0 To 255 Do
					SByteTwo := IncludeSet(Byte(StrToInt(ByteArray[I])), SByteTwo);
			SByte := MulSet(SByte, SByteTwo);
		End
		Else If Number = 6 Then
		Begin
			Write('Добавляемое число: ');
			ReadLn(Value);
			SByte := IncludeSet(Value, SByte)
		End
		Else If Number = 7 Then
		Begin
			Write('Удаляемое число: ');
			ReadLn(Value);
			SByte := ExcludeSet(Value, SByte)
		End
		Else If Number = 8 Then
		Begin
			Write('Множество: { ');
			For I := 0 To 255 Do
				If InSet(I, SByte) Then
					Write(I, ' ');
			WriteLn('}');
		End
		Else
		WriteLn('Число не соответствует диапазону');
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
	End;
	WriteLn('Выход');
End.
