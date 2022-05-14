#!/bin/bash
#c++ multithreading was too difficult

wk="datath"
file="x"
prog="singlePrimeCube"
laso=$(cat ./datath/lastSolve.txt | grep -o '[^ ]\+$' )
end=13238717

tc=11 #tc=[yourThreadCount]-1

trap ctrl_c INT

function ctrl_c() {

	pkill -f ./${prog}
	laso=$( ls ./${wk}/*x.txt | xargs -I {} sh -c "cat {} | tail -1" | sort -n -k4 | head -1 | grep -o '[^ ]\+$' ) #least progressed core 
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

	unbuffer ./${prog} ${tc} ${i} ${laso} ${end} | tee -a ./$wk/${i}${file}".txt" &

done


while true; do
    sleep 1
done