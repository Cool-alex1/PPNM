# CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2     #Werror makes warnings into errors
# LDLIBS += -lstdc++ -lm
# # .PHONEY : all
# # all: Out++.txt

# Out.txt : main
# 	./main > $@

# main : main.o genlist.o
# 	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

# main.o : main.cc
# 	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

CXXFLAGS = -std=c++23 -O1
LDLIBS = -lstdc++

Out.txt: main input.txt
	./main <input.txt >$@ 2>log

main.o:genlist.h

.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) *.o main [Oo]ut* log*

