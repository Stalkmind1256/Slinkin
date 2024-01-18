type ByteSet=set of byte;
Var SByte,SByte2,newSByte,resSByte: ByteSet;
	ByteArray,newArray: Array Of integer;
	
//in
function inSet(e: Byte; bset: ByteSet): Boolean;
var ByteP: PByte;
	ByteN, BitN: byte;
begin
	ByteP:=@bset;
	ByteN := e div 8;
	BitN := e mod 8;
    inSet := ByteP[ByteN] and (1 shl (BitN)) <> 0;
end;

//+
function addSet(b1set,b2set:ByteSet):ByteSet; 
var
	ByteP1,ByteP2:PByte;
	i:byte;
begin
	ByteP1:=@b1set;
	ByteP2:=@b2set;
	for i:=0 to sizeof(ByteSet)-1 do
		ByteP1[i]:=ByteP1[i] or ByteP2[i];
	addSet:=b1set
end;
	
//-
function subSet(b1set,b2set:ByteSet):ByteSet; 
var
	ByteP1,ByteP2:PByte;
	i:byte;
begin
	ByteP1:=@b1set;
	ByteP2:=@b2set;
	for i:=0 to sizeof(ByteSet)-1 do
	    ByteP1[i]:=ByteP1[i] and not ByteP2[i];
    subSet:=b1set;
end;
//*
function mulSet(b1set,b2set:ByteSet):ByteSet;
var
	ByteP1,ByteP2:PByte;
	i:byte;
begin
    ByteP1:=@b1set;
    ByteP2:=@b2set;
    for i:=0 to sizeof(ByteSet)-1 do
	    ByteP1[i]:=ByteP1[i] and ByteP2[i];
    mulSet:=b1set;
end;
// include
function includeSet(e:byte; bset:ByteSet):ByteSet;
Var ByteP: PByte;
	ByteN, BitN: Byte;
Begin
	ByteP := @bset;
	ByteN := e div 8;
	BitN := e mod 8;
	Inc(ByteP, ByteN);
	ByteP^ := ByteP^ + (1 Shl BitN);
	IncludeSet := bset;
End;

//exclude
function excludeSet(e:byte; bset:ByteSet):ByteSet;
Var ByteP: PByte;
	ByteN, BitN: Byte;
Begin
	ByteP := @bset;
	ByteN := e div 8;
	BitN := e mod 8;
	Inc(ByteP, ByteN);
	ByteP^ := ByteP^ and not (1 shl BitN);
	ExcludeSet := bset;
End;

{----------------------------------------}

procedure print(bset:ByteSet);
var i:byte;
begin
	Write('{ ');
	for i := 0 To 255 do
		if InSet(i, bset) then
			Write(i, ' ');
	Write('}');
end;

function create(masiv:array of integer):ByteSet;
var i:byte;
	bset:ByteSet;
	byteP:PByte;
begin
	byteP := @bset;
	for i := 0 to SizeOf(ByteSet) - 1 do
		byteP[i] := 0;
	if length(masiv)<=256 then
		for i := 0 to length(masiv) - 1 do
			bset := IncludeSet(masiv[i], bset)
		else
		for i:= 0 to 255 do
			bset := IncludeSet(masiv[i], bset);
		
	create:=bset;
	
end;

BEGIN

	ByteArray := [1,3,5,7,22,36];
	SByte:=create(ByteArray);
	SByte2:=create(ByteArray);
	write('SByte: ');
	print(SByte);
	writeln;
	write('SByte2: ');
	print(SByte2);
	writeln;
	
	writeln('inSet(22,SByte)');
	writeln(inSet(22,SByte));
	writeln('inSet(11,SByte)');
	writeln(inSet(11,SByte));
	writeln;
	
	writeln('includeSet(107,SByte)');
	SByte:=includeSet(107,SByte);
	write('SByte: ');print(SByte);
	writeln;

	writeln;
	
	writeln('excludeSet(5,SByte)');			
	SByte:=excludeSet(5,SByte);
	write('SByte: ');print(SByte);
	writeln;

	writeln;
	
	newArray:=[4,77,105,107,48];
	newSByte:=create(newArray);
	write('SByte: '); 
	print(SByte); 
	writeln;
	write('newSByte: '); 
	print(newSByte); 
	writeln;

	
	writeln('addSet(SByte,newSByte)');
	resSByte:=addSet(SByte,newSByte);
	print(resSByte);
	writeln;


	
	writeln('subSet(SByte,newSByte)');
	resSByte:=subSet(SByte,newSByte);
	print(resSByte);
	writeln;

	
	writeln('mulSet(SByte,newSByte)');
	resSByte:=mulSet(SByte,newSByte);
	print(resSByte);
	writeln;

	
END. 