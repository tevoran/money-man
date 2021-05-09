CC=x86_64-w64-mingw32-g++

SRC=$(wildcard src/*.cpp)

CFLAGS=-mwindows -o windows/money_man.exe -Lwindows/libs -lSDL2 -lSDL2_ttf -lSDL2_image -Iwindows/include -static-libstdc++ -static-libgcc

main: $(SRC)
	$(CC) $(SRC) $(CFLAGS)


