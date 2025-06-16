CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"



Out.txt: main
	./main > $@


main : main.o matrix.o vector.o runge.o
main.o vector.o matrix.o runge.o: matrix.h vector.h 


plot.harm.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "f(x)"; \
		  set title "blabla"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 0 using 1:2 with lines title "Target func: cos(x)", \
		  	"$<" index 0 using 1:2 with linespoints title "Integral"; \
	' | gnuplot
plot.diffFunc.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "f(x)"; \
		  set title "blabla"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 1 using 1:2 with linespoints title "Integral"; \
	' | gnuplot

plot.scipy1.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "f(x)"; \
		  set title "blabla"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 2 using 1:2 with lines title "Integral"; \
	' | gnuplot

plot.PO1.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "f(x)"; \
		  set title "blabla"; \
		  plot "$<" index 3 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle\
	' | gnuplot
plot.PO2.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "f(x)"; \
		  set title "blabla"; \
		  plot "$<" index 4 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle\
	' | gnuplot
plot.PO3.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "f(x)"; \
		  set title "blabla"; \
		  plot "$<" index 5 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle\
	' | gnuplot





.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut*

