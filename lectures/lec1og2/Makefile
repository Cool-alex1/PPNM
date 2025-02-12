Out.txt : main.exe
	mono $< > $@
	#mono main.exe > Out.txt

main.exe : main.cs hello.dll
	mcs -target:exe -reference:hello.dll -out:main.exe main.cs

hello.dll : hello.cs
	mcs -target:library -out:hello.dll hello.cs

.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) hello.dll main.exe Out.txt

test:
	echo $(RM)