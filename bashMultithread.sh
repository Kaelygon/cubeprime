#!/bin/bash
#c++ multithreading was too difficult

wk="datath"
file="x"

tc=11 #tc=[yourThreadCount]-1

# trap ctrl-c and call ctrl_c()
trap ctrl_c INT

function ctrl_c() {

	pkill -f ./primeCubes
	echo ""
	echo "Quit"
	exit 0
}


for i in $( eval echo {0..$tc} )
do
	echo "" > ./$wk/${i}${file}".txt"
	
	unbuffer ./primeCubes ${tc} ${i} | tee ./$wk/${i}${file}".txt" &

done


while true; do
    sleep 1
done