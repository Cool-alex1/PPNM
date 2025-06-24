CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"


Out.txt: main
	./main  > $@


main : main.o matrix.o vector.o
main.o matrix.o vector.o : matrix.h vector.h


Plot.alpha2.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "α"; \
		  set ylabel "f(v-αΔv)"; \
		  plot \
		  	"$<" index 2 using 1:2 with linespoints title "f_α", \
		  	"$<" index 2 using 1:3 with lines title "f", \
	' | gnuplot
Plot.alpha.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "α"; \
		  set ylabel "f(v-αΔv)"; \
		  plot \
		  	"$<" index 2 using 1:2 with lines title "f", \
	' | gnuplot

Plot.hyd.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "r"; \
		  set ylabel "y"; \
		  plot \
		  	"$<" index 1 using 1:2 with lines, \
	' | gnuplot




.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut*

