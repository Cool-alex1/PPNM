CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"


Out.txt: main
	./main > $@


main : main.o matrix.o vector.o nn.o mini.o QR.o
main.o matrix.o vector.o nn.o mini.o: matrix.h vector.h nn.h mini.h QR.h

Out.plotA.txt: main
	./main --opg Ap > $@
Out.plotB.txt: main
	./main --opg Bp > $@

# %.o : %.cc %.h
# 	@echo MAKING $@ WITH $^
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


Plot.nnFitA.svg : Out.plotA.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "Fit to cos(5x-1)*e^{-x^2} using 8 neurons"; \
		  plot \
		  	"$<" index 1 using 1:2 with lines title "Analytical data", \
		  	"$<" index 1 using 1:3 with lines title "Fit using Gaussian wavelet", \
		  	"$<" index 1 using 1:4 with lines title "Fit using Wavelet", \
	' | gnuplot

Plot.nnFitB.svg : Out.plotB.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "Fit to x*5 using 30 neurons and Gaussian wavelet"; \
		  plot [][-8:8]\
		  	"$<" index 1 using 1:2 with lines title "Analytical data", \
		  	"$<" index 1 using 1:3 with lines title "F_p(x)", \
		  	"$<" index 1 using 1:4 with lines title "dF_p(x)", \
		  	"$<" index 1 using 1:5 with lines title "ddF_p(x)", \
		  	"$<" index 1 using 1:6 with lines title "∫F_p(x)", \
	' | gnuplot



.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut*

