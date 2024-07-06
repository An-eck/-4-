all:
	g++ -std=c++17 -o main main.cpp logic.cpp graphics.cpp -I src/not_ttf/include -L src/not_ttf/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf