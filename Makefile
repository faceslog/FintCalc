CXX = -g++
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=out/%.o)
OUT = a.out

CFLAGS = -Wall -Wextra -Werror -Wshadow -pedantic-errors -O2

$(OUT): $(OBJ)
	$(CXX) $(CFLAGS) -o $@ $^

out/%.o: src/%.cpp | out
	$(CXX) $(CFLAGS) -o $@ -c $<

out:
	mkdir -p $@

clear:
	rm out/*
	rm $(OUT)