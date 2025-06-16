CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"

# # .PHONEY : all
# # all: Out++.txt

# Out.txt : main
# 	./main > $@

# main : main.o genlist.o
# 	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

# main.o : main.cc
# 	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

# CXXFLAGS = -std=c++23 -O1
# LDLIBS = -lstdc++


# Out.txt: matrixTest
# 	./matrixTest > $@
Out.txt: main
	./main > $@

# matrixTest : matrixTest.o matrix.o QR.o
main : main.o matrix.o QR.o

# matrix.o QR.o main.o: matrix.h QR.h
matrixTest.o matrix.o QR.o main.o facTimer.o: matrix.h QR.h


facTimer : facTimer.o matrix.o QR.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o $@ $^





plot.times.svg : out.times.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "size of matrix n x n"; \
		  set ylabel "algorithm runtime (s)"; \
		  f(x) = a*x*x*x ; \
		  a = 0.02; \
		  fit f(x) "$<" via a; \
		  plot \
		  	"$<" index 0 with points title "Runtime of QR factorization",\
		   f(x) title sprintf("a = %3.5f ns",a*1e9)\
	' | gnuplot


out.times.txt: facTimer
	>$@
	for n in $$(seq 100 100 1000); \
		do $(TIME) ./facTimer -n $$n;\
	done




# INCS = matrix.h qrsolver.h

# SRCS = $(INCS:.h=.cc)
# SRCS := $(SRCS:.h=.cc)

# OBJS := $(INCS:.h=.o)
# OBJS := $(OBJS:.h=.o)

# #Create all object files from their corresponding .cc file. Also check if the obj folder even exists
# %.o : %.cc
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# matrix_test : matrix_test.o $(OBJS)

.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) *.o [Oo]ut*

