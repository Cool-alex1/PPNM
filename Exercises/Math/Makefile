CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
.PHONEY : all
all: Out++.txt

Out++.txt : main
	./main > Out++.txt

main : main.o sfuns.o
	$(CXX) $(CXXFLAGS) -o main $^

main.o : main.cc
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut.txt *.o main

test:
	echo $(RM)
	echo $(CXX)