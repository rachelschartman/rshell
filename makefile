#Bash makefile

all: rshell.cpp BaseCmd.h Cmd.h CmdComposer.h Connector.h
	mkdir bin
	g++ rshell.cpp -o bin/rshell
clean:
	rm -rf bin