#!/usr/bin/expect

set timeout 5
set hostname [lindex $argv 0]
log_user 0

spawn ./rshell.exe

# test 1: presence of shell

send_user "         Testing for command prompt.\n"
expect {
    timeout { send_user "\[FAILED\] Show user prompt.\n"; exit 1 }
    eof { send_user "\[FAILED\] Show user prompt.\n"; exit 1 }
    "@$hostname\$ " { send_user "\[PASSED\] Show user prompt.\n" }
}

# test 2: echo command
send_user "         Testing command: echo TEST2\n"
send "echo TEST2\r"
expect {
    timeout { send_user "\[FAILED\] Simple echo test.\n"; exit 1 }
    eof { send_user "\[FAILED\] Simple echo test.\n"; exit 1 }
    "TEST2" { send_user "\[PASSED\] Simple echo test.\n" }
}


# test 3: simple or operation
send_user "         Testing command: echobadcmd || echo goodcmd\n"
expect {
    timeout { send_user "\[FAILED\] Prompt failed to appear after last command!\n"; exit 1 }
    eof { send_user "\[FAILED\] Prompt failed to appear after last command!\n"; exit 1 }
    "@$hostname\$ " { send "touch echobadcmd || echo goodcmd\n" }
}
expect {
    timeout { send_user "\[FAILED\] Simple || operation.\n"; exit 1 }
    eof { send_user "\[FAILED\]  Simple || operation.\n"; exit 1 }
    "goodcmd" { send_user "\[PASSED\] Simple || operation.\n" }
}

# test 4: simple and operation, &&
send_user "         Testing command: echo cmd1 && echo cmd2\n"
expect {
    timeout { send_user "\[FAILED\] Prompt failed to appear after last command!\n"; exit 1 }
    eof { send_user "\[FAILED\] Prompt failed to appear after last command!\n"; exit 1 }
    "@$hostname\$ " { send "echo cmd1 && echo cmd2\n" }
}
expect {
    timeout { send_user "\[FAILED\] Simple && operation.\n"; exit 1 }
    eof { send_user "\[FAILED\]  Simple && operation.\n"; exit 1 }
    "cmd1" { expect {
        "cmd2" { send_user "\[PASSED\] Simple && operation.\n" }
        }
    }
}

# test 5: create, append to a file
send_user "         Testing command: echo fileline1 > testfiles/testfile && cat testfiles/testfile\n"
expect {
    timeout { send_user "\[FAILED\] Prompt failed to appear after last command!\n"; exit 1 }
    eof { send_user "\[FAILED\] Prompt failed to appear after last command!\n"; exit 1 }
    "@$hostname\$ " { send "echo fileline1 > testfiles/testfile; cat testfiles/testfile" }
}
expect {
    timeout { send_user "\[FAILED\] Generating and reading a text file.\n" }
    eof { send_user "\[FAILED\] Generating and reading a text file.\n" }
    "fileline1" { send_user "\[PASSED\] Generating and reading a text file.\n"; send "\r" }
            
}

# test 4: simple or operation
send_user "         Testing command: cat testfiles/testfile | grep -i line5\n"
expect {
    timeout { send_user "\[FAILED\] Prompt failed to appear after last command! (timeout)\n"; exit 1 }
    eof { send_user "\[FAILED\] Prompt failed to appear after last command! (eof)\n"; exit 1 }
    "@$hostname\$ " { 
        send "echo fileline2 >> testfiles/testfile\r";
        send "echo fileline3 >> testfiles/testfile\r";
        send "echo fileline4 >> testfiles/testfile\r";
        send "echo fileline5 >> testfiles/testfile\r";
        send "echo fileline6 >> testfiles/testfile\r";
        send "cat testfiles/testfile | grep -i line5\r" 
    }
}
expect {
    timeout { send_user "\[FAILED\] Piped command.\n"; exit 1 }
    eof { send_user "\[FAILED\]  Piped command.\n"; exit 1 }
    "fileline5" { send_user "\[PASSED\] Piped command.\n" }
}