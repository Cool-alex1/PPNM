CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"


all: Out.txt out.erf.txt out.erf.svg 

Out.txt: main
	./main > $@


main : main.o vector.o Quad.o
erfplotter : erfplotter.o vector.o Quad.o
main.o erfplotter.o vector.o Quad.o: vector.h 


out.erf.txt: erfplotter
	>$@
	for n in $$(seq 52 -1 0); \
		do ./erfplotter -acc $$n >> $@; \
	done

Plot.erf.svg : out.erf.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "acc"; \
		  set ylabel "|error|"; \
		  set title "Error function absolute error between tabulated and calculated value for erf(1)"; \
		  set key left; \
		  set logscale x 2; \
		  set logscale y 2; \
		  plot [][1e-16 : 0.1] \
		  	"$<" index 0 with linespoints pointtype 1 title "error", \
	' | gnuplot


.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut* *.o *.svg main erfplotter

