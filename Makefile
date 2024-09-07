main: main.c
	clang main.c -o main -lraylib -lm -lpthread -ldl -lrt && ./main
