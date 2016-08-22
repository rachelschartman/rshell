#Bash makefile

flags=-Wall -Werror -ansi -pedantic

all: src/rshell.cpp src/BaseCmd.h src/Cmd.h src/CmdComposer.h src/Connector.h
	[ -d "bin" ] || mkdir bin
	g++ $(flags) src/rshell.cpp -o bin/rshell
rshell:
	all: src/rshell.cpp src/BaseCmd.h src/Cmd.h src/CmdComposer.h src/Connector.h
	[ -d "bin" ] || mkdir bin
	g++ $(flags) src/rshell.cpp -o bin/rshell
clean:
	rm -rf bin