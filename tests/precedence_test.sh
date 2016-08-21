(echo hello)
(echo ls || (echo world))
(echo hello); (echo good bye)
(echo school;
echo bob)
ls -j && echo world || echo this should output
ls -j && (echo world || echo this should output)
ls -j || (echo world && echo this should output)
(ls -j || echo world) && echo this should output
echo test || (ls -j || (echo world && echo test))
(echo "whiskey tango foxtrot :-)")
