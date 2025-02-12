CXXFLAGS += -Wall -Wextra -std=c++23 -fwrapv#-ferror-limit=1
#-ferror-limit=1 == stopper efter 1 fejl er fundet
LDLIBS += -lstdc++ -lm
CODE = $(filter %.cs,$^)
DLLS = $(addprefix -reference:,$(filter %.dll,$^))
MKLIB = mcs -out:$@ -target:library $(DLLS) $(CODE) 
MKEXE = mcs -out:$@ -target:exe $(DLLS) $(CODE) 
# .PHONEY : all
# all: Out.txt Out++.txt

Out.txt : main ; ./main > $@

main : main.o
main.o: main.cc