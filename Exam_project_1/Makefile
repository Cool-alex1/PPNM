CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"


all: Out.txt Plots/Plot.hydrogen.svg Plots/Plot.R.svg Plots/Plot.speed.svg


Out.txt: main
	./main  > $@

Out.data.txt: main
	./main -mode plot > $@

Out.speed.txt: main
	>$@
	for n in $$(seq 10 10 150); \
		do $(TIME) ./main -mode speed -size $$n;\
	done


main : main.o newton.o Helper/matrix.o Helper/vector.o
main.o newton.o Helper/matrix.o Helper/vector.o : Helper/matrix.h Helper/vector.h newton.h



Plots/Plot.hydrogen.svg : Out.data.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "r"; \
		  set ylabel "f(r)"; \
		  set title "Calculated wavefunction for v_{min} and v_{min2}"; \
		  plot \
		  	"$<" index 1 using 1:2 with lines title "v_{min}", \
		  	"$<" index 3 using 1:2 with lines title "v_{min2}"; \
	' | gnuplot
Plots/Plot.R.svg : Out.data.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "Iterations"; \
		  set ylabel "R"; \
		  set title "Calculations for λ_{min2} with a too high accuracy"; \
		  plot [][-0.6:0.5] \
		  	"$<" index 0 using 0:1 with lines title "λ_{min}", \
		  	"$<" index 2 using 0:1 with lines title "λ_{min2}"; \
	' | gnuplot
Plots/Plot.speed.svg : Out.speed.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "Size of matrix n x n"; \
		  set ylabel "algorithm runtime (s)"; \
		  f(x) = a*x*x*x ; \
		  a = 0.02; \
		  fit f(x) "$<" via a; \
		  plot \
		  	"$<" index 0 with points title "Runtime of R(H, v) minimization",\
			f(x) title sprintf("a*x^3, a = %3.5f ns",a*1e9)\
	' | gnuplot




.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut* *.svg *.o main Plots/*.svg Helper/*.o *.log

