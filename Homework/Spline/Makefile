CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"


.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
all: Out.txt plot.lin.svg plot.quard.svg

Out.txt: main
	./main > $@


main : main.o vector.o spline.o
main.o vector.o spline.o: vector.h 


out.lin.txt: main
	./main -mode lin > $@; 
plot.lin.svg : out.lin.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "f(x)"; \
		  set title "Linear spline"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 0 using 1:2 with lines title "Target func: cos(x)", \
		  	"$<" index 1 using 1:2 with lines title "∫cos(x)dx", \
		  	"$<" index 2 using 1:2 with points title "Spline", \
		  	"$<" index 3 using 1:2 with points title "Integral"; \
	' | gnuplot

out.quard.txt: main
	./main -mode "quard" > $@; 
plot.quard.svg : out.quard.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "f(x)"; \
		  set title "Quadratic spline"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 0 using 1:2 with lines title "Target func: cos(x)", \
		  	"$<" index 1 using 1:2 with lines title "∫cos(x)dx", \
		  	"$<" index 2 using 1:2 with points title "Integral", \
		  	"$<" index 4 using 1:2 with linespoints title "Derivative", \
		  	"$<" index 3 using 1:2 with points title "Spline"; \
	' | gnuplot



clean:
	$(RM) [Oo]ut* *.o *.svg main

