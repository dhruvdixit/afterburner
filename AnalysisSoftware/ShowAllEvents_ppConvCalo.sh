#/bin/bash

#Read the different cuts form the Cut selection log file
echo $1
echo $2
echo $3
InputFiles=`cat $2`
for inputFile in $InputFiles; do
	echo $inputFile
# 	runnumber=`cat runNumbersLHC11a_pass4_wSDD.txt`	
	runnumber=$(echo $inputFile | cut -d "/" -f $4)
	echo $runnumber
	root -l -b -q -x GetEventStats.C\+\+\(\"$inputFile\"\,\"$3\"\,$runnumber\,\"$1\"\,\"pp2760GeV\"\,\"GammaConvCalo_1\"\)
done
