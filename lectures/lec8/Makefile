CXXFLAGS = -Wall -std=c++23 -O3 -ffast-math
CODE = $(filter %.cs,$^)
LIBS = $(addprefix -reference:,$(filter %.dll,$^))
MKEXE = mcs -target:exe -out:$@ $(LIBS) $(CODE)
MKLIB = mcs -target:library -out:$@ $(LIBS) $(CODE)
TIME = time --output=$@ --append --format "$$nthreads %e %U"

# test: out1 out2 out3 out4

# out1: main.exe ; mono $< -terms 5e8 >$@ 2>log1
# out2: main.exe ; mono $< -terms 5e8 >$@ 2>log2
# out3: main.exe ; mono $< -terms 5e8 >$@ 2>log3
# out4: main.exe ; mono $< -terms 5e8 >$@ 2>log4

# test2 : main.exe
# 	mono $< -terms 5e8 >out1 2>log1 &
# 	mono $< -terms 5e8 >out2 2>log2 &
# 	mono $< -terms 5e8 >out3 2>log3 &
# 	mono $< -terms 5e8 >out4 2>log4 &

# test3 : main.exe
# 	for n in 1 2 3 4; do mono main.exe -terms 5e8 >out$$n >log$$n &; done