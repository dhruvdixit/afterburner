#/bin/bash

#Read the different cuts form the Cut selection log file
echo $1
echo $2
echo $3
InputFiles=`cat $2`
for inputFile in $InputFiles; do
	echo $inputFile
	runnumber=`cat LHC11h_AOD145_goodruns.txt`	
	runnumber=$(echo $inputFile | cut -d "/" -f $4)
	echo $runnumber
	root -l -b -q -x GetEventStats.C\+\+\(\"$inputFile\"\,\"$3\"\,$runnumber\,\"$1\"\,\"HI\"\,\"GammaConvV1_56\"\)
done
