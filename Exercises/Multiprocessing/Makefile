CXXFLAGS = -Wall -std=c++23 -O3 -ffast-math
CODE = $(filter %.cs,$^)
LIBS = $(addprefix -reference:,$(filter %.dll,$^))
MKEXE = mcs -target:exe -out:$@ $(LIBS) $(CODE)
MKLIB = mcs -target:library -out:$@ $(LIBS) $(CODE)
TIME = time --portability --output=$@ --append --format "$$nthreads %e %U"

Times.png : out.times.txt Makefile
	echo '\
		set term png ;\
		set out "$@" ;\
		set title "program running time as function of number of threads" ;\
		set xlabel "number of threads" ;\
		set ylabel "running time [sec]" ;\
		plot \
			"$<" index 0 with linespoints title "C++" \
			,"$<" index 1 with linespoints title "C#" \
	'|tee log.gpi|gnuplot




N=3e8
out.times.txt: main Makefile #main.exe
	>$@
	for nthreads in `seq 10`; \
		do $(TIME) ./main -threads $$nthreads -terms $(N) ;\
	done
	echo "\n" >> $@
	for nthreads in `seq 10`; \
		do $(TIME) mono main.exe -threads $$nthreads -terms $(N) ;\
	done

clean:
	$(RM) main main.exe [Ll]og* [Oo]ut* *.png *.txt


main.exe: main.cs ; $(MKEXE)