CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"



all: Out.txt Out_A.txt Out_B.txt Out_C.txt out.UnitCir.txt out.UnitCirB.txt plot.cirErr.svg plot.cirErrB.svg 


Out.txt: main
	./main > $@

Out_A.txt: main
	./main --opg A > $@

Out_B.txt: main
	./main --opg B > $@

Out_C.txt: main
	./main --opg C > $@

out.UnitCir.txt: main
	>$@
	for n in $$(seq 8 1 40); \
		do ./main --opg A --Npow $$n >> $@; \
	done

out.UnitCirB.txt: main
	>$@
	for n in $$(seq 8 1 40); \
		do ./main --opg B --Npow $$n >> $@; \
	done



main : main.o vector.o
main.o vector.o : vector.h




plot.cirErr.svg : out.UnitCir.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "N"; \
		  set ylabel "err"; \
		  set title "Error dependency of counts number (N) on a unit circle with plain MC"; \
		  set logscale x 2; \
		  f(x) = a/sqrt(x) ; \
		  a = 0.02; \
		  fit f(x) "$<" index 0 using 1:3 via a; \
		  plot \
		  	"$<" index 0 using 1:2 with point title "Estimated err", \
		    f(x) title sprintf("a/sqrt(N) fit, a = %3.5f",a),\
		  	"$<" index 0 using 1:3 with point title "Actual err" \
	' | gnuplot
plot.cirErrB.svg : out.UnitCirB.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key left; \
		  set xlabel "N"; \
		  set ylabel "err"; \
		  set title "Error dependency of counts number (N) on a unit circle with MC using quasi-random sequences"; \
		  set logscale x 2; \
		  f(x) = a/sqrt(x) ; \
		  a = 0.02; \
		  fit f(x) "$<" index 0 using 1:3 via a; \
		  plot \
		  	"$<" index 0 using 1:2 with point title "Estimated err", \
		    f(x) title sprintf("a/sqrt(N) fit, a = %3.5f",a),\
		  	"$<" index 0 using 1:3 with point title "Actual err" \
	' | gnuplot


.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut* *.o *.svg *.log main

