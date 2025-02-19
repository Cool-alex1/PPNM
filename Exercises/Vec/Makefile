CXXFLAGS += -Wall -std=c++23 #-ferror-limit=1 
LDLIBS += -lstdc++ -lm
Out.txt:test
	./$< > $@
test : test.o vec.o
test.o vec.o: vec.h