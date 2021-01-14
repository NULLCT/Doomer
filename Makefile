FLAG = -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
INCLUDE = -I /usr/local/include

main: src/main.cpp
	clang++ src/main.cpp -o sfmlapp $(INCLUDE) $(FLAG)
