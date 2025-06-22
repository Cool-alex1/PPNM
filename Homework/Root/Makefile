CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"


Out.txt: main
	./main  > $@


main : main.o matrix.o QR.o vector.o root.o runge.o
main.o matrix.o vector.o QR.o root.o runge.o: matrix.h vector.h root.h runge.h

Out.maxCon.txt: main
	./main --mode p1 > $@
Out.minCon.txt: main
	./main --mode p2 > $@
Out.accCon.txt: main
	./main --mode p3 > $@
Out.epsCon.txt: main
	./main --mode p4 > $@


Plot.rmaxCon.svg : Out.maxCon.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "r_{max} convergens"; \
		  f(x) = x*exp(-x); \
		  plot [0:8][]\
		  	f(x) with lines title "Analytical solution", \
		  	"$<" index 0 using 1:2 with lines title "r_{max} = 1", \
		  	"$<" index 1 using 1:2 with lines title "r_{max} = 2", \
		  	"$<" index 2 using 1:2 with lines title "r_{max} = 4", \
		  	"$<" index 3 using 1:2 with lines title "r_{max} = 8", \
		  	"$<" index 4 using 1:2 with lines title "r_{max} = 16"; \
	' | gnuplot
Plot.rminCon.svg : Out.minCon.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "r_{min} convergens"; \
		  f(x) = x*exp(-x); \
		  plot [0:8][]\
		  	f(x) with lines title "Analytical solution", \
		  	"$<" index 0 using 1:2 with lines title "r_{min} = 0.001", \
		  	"$<" index 1 using 1:2 with lines title "r_{min} = 0.01", \
		  	"$<" index 2 using 1:2 with lines title "r_{min} = 0.1", \
		  	"$<" index 3 using 1:2 with lines title "r_{min} = 0.25", \
		  	"$<" index 4 using 1:2 with lines title "r_{min} = 0.5"; \
	' | gnuplot
Plot.accCon.svg : Out.accCon.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "acc convergens"; \
		  f(x) = x*exp(-x); \
		  plot [0:8][]\
		  	f(x) with lines title "Analytical solution", \
		  	"$<" index 0 using 1:2 with lines title "acc = 1e-5", \
		  	"$<" index 1 using 1:2 with lines title "acc = 1e-4", \
		  	"$<" index 2 using 1:2 with lines title "acc = 1e-3", \
		  	"$<" index 3 using 1:2 with lines title "acc = 1e-2", \
		  	"$<" index 4 using 1:2 with lines title "acc = 1e-1", \
		  	"$<" index 5 using 1:2 with lines title "acc = 1"; \
	' | gnuplot
Plot.epsCon.svg : Out.epsCon.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "eps convergens"; \
		  f(x) = x*exp(-x); \
		  plot [0:8][]\
		  	f(x) with lines title "Analytical solution", \
		  	"$<" index 0 using 1:2 with lines title "acc = 1e-5", \
		  	"$<" index 1 using 1:2 with lines title "acc = 1e-4", \
		  	"$<" index 2 using 1:2 with lines title "acc = 1e-3", \
		  	"$<" index 3 using 1:2 with lines title "acc = 1e-2", \
		  	"$<" index 4 using 1:2 with lines title "acc = 1e-1", \
		  	"$<" index 5 using 1:2 with lines title "acc = 1"; \
	' | gnuplot


.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut*

