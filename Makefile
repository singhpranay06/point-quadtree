all:
	g++ -I src/include -L src/lib -o main main.cpp Grid.cpp Cell.cpp -lmingw32 -lSDL2main -lSDL2