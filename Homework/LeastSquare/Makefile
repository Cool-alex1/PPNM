CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"



Out.txt: main
	./main > $@


main : main.o matrix.o QR.o lsFit.o
main.o matrix.o QR.o lsFit.o: matrix.h QR.h lsFit.h

# lin fit
# plot.fit.svg : Out.txt Makefile
# 	echo 'set terminal svg background "white"; \
# 		  set output "$@"; \
# 		  set key right; \
# 		  set xlabel "x"; \
# 		  set ylabel "y"; \
# 		  a = 3.01314; \
# 		  b = -0.0456365; \
# 		  aerr = 0.161636; \
# 		  berr = 1.04409; \
# 		  f(x) = a*x + b ; \
# 		  g(x) = (a-aerr)*x + (b-berr) ; \
# 		  h(x) = (a+aerr)*x + (b+berr) ; \
# 		  plot \
# 		  	"$<" index 1 with yerrorbars title "datapoints",\
# 		   f(x) title sprintf("F_c = ax + b",a,b),\
# 		   g(x) title sprintf("F_{c - dc}",a),\
# 		   h(x) title sprintf("F_{c + dc}",a)\
# 	' | gnuplot

plot.fit.svg : Out.txt Makefile
	echo 'set terminal svg background "white"; \
		  set output "$@"; \
		  set key right; \
		  set xlabel "t"; \
		  set ylabel "y"; \
		  a = 4.95866; \
		  λ = 0.170624; \
		  aerr = 0.0354019; \
		  λerr = 0.00715662; \
		  f(x) = exp(-λ*x + a) ; \
		  g(x) = exp(-(λ + λerr)*x + (a - aerr)) ; \
		  h(x) = exp(-(λ - λerr)*x + (a + aerr)) ; \
		  plot \
		  	"$<" index 1 with yerrorbars title "datapoints",\
		   f(x) title sprintf("F_c = e^{-%3.4f*t + %3.4f}",λ,a),\
		   g(x) title sprintf("F_{c - dc}",a),\
		   h(x) title sprintf("F_{c + dc}",a)\
	' | gnuplot


.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) *.o [Oo]ut*

