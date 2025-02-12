CXXFLAGS += -Wall -Wextra -std=c++23 #-ferror-limit=1
#-ferror-limit=1 == stopper efter 1 fejl er fundet
LDLIBS += -lstdc++ -lm
CODE = $(filter %.cs,$^)
DLLS = $(addprefix -reference:,$(filter %.dll,$^))
MKLIB = mcs -out:$@ -target:library $(DLLS) $(CODE) 
MKEXE = mcs -out:$@ -target:exe $(DLLS) $(CODE) 

Out.txt : main.exe
	mono $< > $@
	./main > $@

main.exe : main.cs vec.dll; $(MKEXE)

vec.dll : vec.cs ; $(MKLIB)

main : main.o vec.h
main.o: main.cc vec.h
vec.o: vec.cc vec.h
