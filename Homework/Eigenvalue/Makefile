CXXFLAGS += -Wall -Wextra -Werror -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"


# main : main.o genlist.o
# 	$(CXX) $(CXXFLAGS) $(LDLIBS) -o main $^

# main.o : main.cc
# 	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

# CXXFLAGS = -std=c++23 -O1
# LDLIBS = -lstdc++


Out.txt: eigenValTest
	./eigenValTest > $@


eigenValTest : eigenValTest.o matrix.o eigenD.o
eigenValTest.o matrix.o eigenD.o speedTest.o: matrix.h eigenD.h


Out.Ham.txt: ham
	./ham -rmax 10 -dr 0.3 > $@
ham : ham.o matrix.o eigenD.o
ham.o: matrix.h eigenD.h


out.rmax_convergence.txt: ham
	>$@
	for n in $$(seq 0.7 0.1 7); \
		do ./ham -rmax $$n -dr 0.1 >> $@; \
	done
plot.rmax_convergence.svg : out.rmax_convergence.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set key right; \
		  set xlabel "rmax (r_0)"; \
		  set ylabel "ε_0"; \
		  set title "convergence of ground state energy in r_{max}"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 0 using 1:3 with linespoints title "ground state energy"; \
	' | gnuplot

out.dr_convergence.txt: ham
	>$@
	for n in $$(seq 0.1 0.1 5); \
		do ./ham -rmax 15 -dr $$n >> $@; \
	done
plot.dr_convergence.svg : out.dr_convergence.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "dr (r_0)"; \
		  set ylabel "ε_0"; \
		  set title "convergence of ground state energy in Δr"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 0 using 2:3 with linespoints title "ground state energy"; \
	' | gnuplot

out.waveFuncs.txt : ham
	./ham -rmax 10 -dr 0.05 -wf 5 > $@
plot.waveFuncs.svg : out.waveFuncs.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "r"; \
		  set ylabel "f(r)"; \
		  set title "Solved eigen-functions"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 1 using 1:2 with lines title "f_1", \
		  	"$<" index 2 using 1:2 with lines title "f_2", \
		  	"$<" index 3 using 1:2 with lines title "f_3", \
		  	"$<" index 4 using 1:2 with lines title "f_4", \
		  	"$<" index 5 using 1:2 with lines title "f_5"; \
	' | gnuplot



speedTest : speedTest.o matrix.o eigenD.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o $@ $^

out.speed.txt: speedTest
	>$@
	for n in $$(seq 50 50 400); \
		do $(TIME) ./speedTest -n $$n;\
	done
	
plot.speed.svg : out.speed.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "size of matrix n x n"; \
		  set ylabel "algorithm runtime (s)"; \
		  f(x) = a*x*x*x ; \
		  a = 0.02; \
		  fit f(x) "$<" via a; \
		  plot \
		  	"$<" index 0 with points title "Runtime of eigenvalue decomp",\
		   f(x) title sprintf("a = %3.5f ns",a*1e9)\
	' | gnuplot


.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) *.o [Oo]ut*

