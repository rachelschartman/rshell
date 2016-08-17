**SUMMARY OF PROJECT**: This project is an emulation of bash. It is capable of executing
                        any one line command entered after the prompt, which takes the
                        format of loginID@hostMachine$ [command arguments go here]. When
                        a command is entered the CmdComposer takes the line of text
                        and turns it into a tree of Cmd and Connector classes which is
                        then executed by calling the execute function on the root node.
                        
**COMPILATION**:        To compile this program and run it all you have to do is run
                        $make and then $bin/rshell from the Cs100Assn2 directory and
                        and the program will start.
                 
**KNOWN BUGS**:         The terminal cannot accept arrow-key entries on a keyboard.