Out.txt : Makefile main.exe input.txt main
	echo "hello" > $@
	echo 1,2 1,3 1,4 | sed --expression "s/,/\./g" >> $@
	echo "hello world for stdin" | mono main.exe 23,23 44,44 55,55 1>> $@ 2> log
	cat input.txt | mono main.exe 1>> $@ 2>> log
	mono main.exe <input.txt 1>> $@ 2>> log
	echo " " | mono main.exe -input:input.txt -output:$@ 2>> log
	./main -input input.txt -output $@ 2>> log



#ved 1>>, 1> normal output = 1, erroroutput = 2

input.txt : Makefile
	echo "these go $@" > $@

main.exe : main.cs
	mcs -target:exe -out:$@ $<

test:
	echo $@
	echo '$@'
	echo "$@"