CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"


Out.txt: main
	./main --input higgs.data.txt --output 0 > $@

higgs_fit.txt: main
	./main --input higgs.data.txt --output higgs > $@


main : main.o matrix.o QR.o vector.o mini.o
main.o matrix.o vector.o QR.o mini.o: matrix.h vector.h mini.h


# %.o : %.cc %.h
# 	@echo MAKING $@ WITH $^
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

Plot.higgs.svg : higgs.data.txt higgs_fit.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set xlabel "Energy [GeV]"; \
		  set ylabel "σ [arb. units]"; \
		  plot \
		  	"$<" with errorbars pointtype 7 title "experimental data",\
			"higgs_fit.txt" with lines title "fit"\
	' | gnuplot




plot.Rosen.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "blabla"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 0 using 0:1 with lines title "Rosen route", \
	' | gnuplot
plot.Himmel.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "blabla"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 1 using 0:1 with lines title "Himmel route", \
	' | gnuplot
plot.Beale.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "blabla"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 2 using 0:1 with lines title "Beale route", \
	' | gnuplot





.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut*

