CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"


Out.txt: main
	./main > $@




main : main.o matrix.o vector.o nn.o mini.o QR.o
main.o matrix.o vector.o nn.o mini.o: matrix.h vector.h nn.h mini.h QR.h


# %.o : %.cc %.h
# 	@echo MAKING $@ WITH $^
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


Plot.nn.svg : Out.txt Makefile
	echo 'set terminal svg background "white";\
		  set output "$@"; \
		  set xlabel "x"; \
		  set ylabel "y"; \
		  set title "blabla"; \
		  plot \
		  	"$<" index 1 using 1:2 with lines title "Data", \
		  	"$<" index 2 using 1:2 with lines title "Fit", \
	' | gnuplot



.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) [Oo]ut*

