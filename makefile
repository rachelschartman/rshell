#Bash makefile

all: src/rshell.cpp src/BaseCmd.h src/Cmd.h src/CmdComposer.h src/Connector.h
	[ -d "bin" ] || mkdir bin
	g++ src/rshell.cpp -o bin/rshell
clean:
	rm -rf bin