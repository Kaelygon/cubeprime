#!/bin/bash
#c++ multithreading was too difficult

wk="datath"
file="x"
prog="singlePrimeCube"
laso=$(cat ./datath/lastSolve.txt | grep -o '[^ ]\+$' )

tc=10 #tc=[yourThreadCount]-1

trap ctrl_c INT

function ctrl_c() {

	pkill -f ./${prog}
	laso=$(ls ./${wk}/*x.txt | xargs cat | tail -n 1 | sort -n | head -n 1 | grep -o '[^ ]\+$' )
	echo "laso: $laso"

	echo -n $laso > ./$wk/lastSolve.txt

	echo ""
	echo "Quit"
	exit 0
}

if ! [[ $yournumber =~ $re ]] ; then
   laso=0
fi
echo "laso: $laso"

for i in $( eval echo {0..$tc} )
do

	unbuffer ./${prog} ${tc} ${i} ${laso} | tee -a ./$wk/${i}${file}".txt" &

done


while true; do
    sleep 1
done