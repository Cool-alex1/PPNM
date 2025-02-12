CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS += -lstdc++ -lm
.PHONEY : all
all: Out.txt Out++.txt

Out.txt : main.exe
	mono $< > $@
	#mono main.exe > Out.txt

Out++.txt : main
	./main > Out++.txt

main : main.o sfuns.o
	$(CXX) $(CXXFLAGS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

main.exe : main.cs sfuns.dll
	mcs -target:exe -reference:sfuns.dll -out:main.exe main.cs

sfuns.dll : sfuns.cs
	mcs -target:library -out:sfuns.dll sfuns.cs

.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) sfuns.dll main.exe [Oo]ut.txt *.o main

test:
	echo $(RM)
	echo $(CXX)