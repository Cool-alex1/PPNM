CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"



Out.txt: main
	./main --input higgs.data.txt > $@


main : main.o matrix.o QR.o vector.o mini.o
main.o matrix.o vector.o QR.o mini.o: matrix.h vector.h mini.h
# vector.o: vector.h vector.cc matrix.h matrix.cc QR.h QR.cc mini.h mini.cc
# matrix.o: vector.h vector.cc matrix.h matrix.cc QR.h QR.cc mini.h mini.cc
# main.o QR.o mini.o: vector.h vector.cc matrix.h matrix.cc QR.h QR.cc mini.h mini.cc



# %.o : %.cc %.h
# 	@echo MAKING $@ WITH $^
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@



out.lin.txt: main
	./main -mode "lin" > $@; 
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

out.quard.txt: main
	./main -mode "quard" > $@; 
plot.quard.svg : out.quard.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "f(x)"; \
		  set title "blabla"; \
		  set datafile separator comma; \
		  plot \
		  	"$<" index 1 using 1:2 with lines title "Target func: cos(x)", \
		  	"$<" index 2 using 1:2 with lines title "∫cos(x)dx", \
		  	"$<" index 3 using 1:2 with points title "Integral", \
		  	"$<" index 5 using 1:2 with linespoints title "Derivative", \
		  	"$<" index 4 using 1:2 with lines title "Spline"; \
	' | gnuplot



.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut*

