all: compile run
compile:
	gcc src/main.c -o bin/cfse.exe

run:
	bin/cfse.exe