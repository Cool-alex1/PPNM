CXXFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter -std=c++23 -O2     #Werror makes warnings into errors
LDLIBS += -lstdc++ -lm
TIME = time --portability --append --output=$@ --format "$$n %e"




vector.o matrix.o : matrix.h vector.h 





.PHONEY:clean #Er her i tilfælde af at vi har en fil der hedder clean
clean:
	$(RM) *.o [Oo]ut*

