CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm
# CSLIBS = -reference:System.Numerics.dll
CODE = $(filter %.cs,$^)
LIBS = $(addprefix -reference:,$(filter %.dll,$^))
MKEXE = mcs -target:exe -out:$@ $(LIBS) $(CODE)
MKLIB = mcs -target:library -out:$@ $(LIBS) $(CODE)

all: plot.test.svg


#Her laver man grafen i Makefile
plot.gamma.svg : data.txt Makefile
	echo '\
	set terminal svg background "white"; \
	set output "$@"; \
	plot \
		"$<" index 1 with lines title "Γ(x+1)"\
		,"$<" index 2 with points title "x!"\
		,"$<" index 3 with lines title "√(2πn)*(n/e)^n"\
	' | tee log.erf.gp | gnuplot
#index 1 betyder at den tager data klump nr. 2 som bliver skabt af main.cs

#set terminal svg (den her linje laver billedet til see through)
plot.erf.svg : data.txt Makefile          #Her laver man grafen i Makefile
	echo '\
	set terminal svg background "white"; \
	set output "$@"; \
	plot "$<" index 0 with lines ;\
	' | tee log.erf.gp | gnuplot¨


plot.lngamma.svg : data.txt Makefile          #Her laver man grafen i Makefile
	echo '\
	set terminal svg background "white"; \
	set output "$@"; \
	plot "$<" index 4 with lines ;\
	' | tee log.erf.gp | gnuplot

plot.test.svg: test.gp                    #Og her er koden til grafen i test.gp
	gnuplot $<

data.txt : main.exe
	mono $< > $@
# Out.txt: main.exe

sfuns.dll : sfuns.cs ; $(MKLIB)
main.exe : main.cs sfuns.dll ; $(MKEXE)

clean:
	$(RM) *.exe *.dll [Oo]ut* [Ll]og*