[ -d bin ] #should just output (True) unless preceded by 
[ -d bin ] && rm -rf bin #removes bin if bin exists
[ comments.tx ] && rm comments.tx #removes comments.tx 
test -d bin #just outputs (True) again
test -d bin && rm -rf bin #rmoves
test -f bin && (rm -rf bin || (echo hello && echo world))
test -f "SUMMER16.txt" && (echo good times)