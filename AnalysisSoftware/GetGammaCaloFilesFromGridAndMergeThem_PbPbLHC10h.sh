#! /bin/bash

# copies files from grid
# creates directory
# changes internal structure
# merges files according to the pPb needs

if [ $1 = "fbock" ]; then 
   BASEDIR=/mnt/additionalStorage/OutputLegoTrains/PbPb
elif [ $1 = "fbockGSI" ]; then 
   BASEDIR=/hera/alice/fbock/Grid/OutputLegoTrains/PbPb
elif [ $1 = "leardini" ]; then 
   BASEDIR=/Users/lucy/
elif [ $1 = "leardiniALICESERV1" ]; then 
   BASEDIR=/alidata50/alice_u/leardini/GridOutput/PbPb/
elif [ $1 = "leardiniGSI" ]; then 
   BASEDIR=/hera/alice/leardini/Grid/OutputLegoTrains/PbPb
elif [ $1 = "passfeld" ]; then 
   BASEDIR=~/work/Gridoutput/PbPb
elif [ $1 = "passfeldMAF" ]; then 
   BASEDIR=/data9/a_pass02/gamma_test/AnalysisSoftware/LegoTrain/
elif [ $1 = "passfeldGSI" ]; then  
   BASEDIR=/hera/alice/passfeld/Grid/OutputLegoTrains/PbPb
elif [ $1 = "amarin" ]; then     
   BASEDIR=/Users/marin/
elif [ $1 = "amarinGSI" ]; then     
   BASEDIR=/hera/alice/marin/Grid/OutputLegoTrains/PbPb 
elif [ $1 = "amarinALICESERV1" ]; then     
   BASEDIR=/alidata50/alice_u/amarin/GridOutput/PbPb/   
elif [ $1 = "mwilde" ]; then        
   BASEDIR=~/work/GridOutput 
elif [ $1 = "mwildeGSI" ]; then           
   BASEDIR=/hera/alice/mwilde/Grid/OutputLegoTrains/PbPb 
elif [ $1 = "pgonzales" ]; then     
   BASEDIR=~/work/GridOutput 
elif [ $1 = "pgonzalesGSI" ]; then        
   BASEDIR=/hera/alice/pgonzales/Grid/OutputLegoTrains/PbPb
elif [ $1 = "dmuhlheim" ]; then 
   BASEDIR=/home/daniel/Desktop/Grid
fi
mkdir -p $BASEDIR
  
# 	TRAINDIR=Legotrain-vAN-20141110-Calo
# 	LHC10hData=143_20141111-1838; #ESD
# 	LHC13d2=174_20141111-1927; #ESD
# 	LHC13d2b=175_20141111-1927; #ESD 

	TRAINDIR=Legotrain-vAN-20141116-Calo
# 	LHC10hData=145_20141117-1516; #ESD
	LHC10hData=146_20141117-1516; #ESD
# 	LHC13d2=178_20141117-1308; #ESD
	LHC13d2=180_20141117-1317; #ESD
# 	LHC13d2b=179_20141117-1313; #ESD 
	LHC13d2b=181_20141117-1319; #ESD 
	
OUTPUTDIR=$BASEDIR/$TRAINDIR
if [ $2 = "AODdata" ]; then
   TRAINPATHData=GA_PbPb_AOD
else
   TRAINPATHData=GA_PbPb
fi   
OUTPUTDIR_LHC10h_A=$BASEDIR/$TRAINDIR/$TRAINPATHData-$LHC10hData-allRuns

if [ $3 = "AODmc" ]; then
   TRAINPATHMC=GA_PbPb_MC_AOD
else
   TRAINPATHMC=GA_PbPb_MC
fi   
OUTPUTDIR_LHC13d2_A=$BASEDIR/$TRAINDIR/$TRAINPATHMC-$LHC13d2-allRuns
OUTPUTDIR_LHC13d2b_A=$BASEDIR/$TRAINDIR/$TRAINPATHMC-$LHC13d2b-allRuns
# OUTPUTDIR_LHC14a1c_A=$BASEDIR/$TRAINDIR/$TRAINPATHMC-$LHC14a1c-allRuns


mkdir -p $OUTPUTDIR_LHC10h_A
mkdir -p $OUTPUTDIR_LHC13d2_A
mkdir -p $OUTPUTDIR_LHC13d2b_A

alien_cp alien:/alice/cern.ch/user/a/alitrain/PWGGA/$TRAINPATHMC/$LHC13d2/merge/GammaCalo* file:$OUTPUTDIR_LHC13d2_A/
alien_cp alien:/alice/cern.ch/user/a/alitrain/PWGGA/$TRAINPATHMC/$LHC13d2b/merge/GammaCalo* file:$OUTPUTDIR_LHC13d2b_A/
alien_cp alien:/alice/cern.ch/user/a/alitrain/PWGGA/$TRAINPATHData/$LHC10hData/merge/GammaCalo* file:$OUTPUTDIR_LHC10h_A/


if [ $3 = "AODmc" ]; then
   ls $OUTPUTDIR_LHC13d2_A/GammaCalo_*.root > fileLHC13d2.txt
   fileNumbers=`cat fileLHC13d2.txt`
   for fileName in $fileNumbers; do
      echo $fileName
      number=`echo $fileName  | cut -d "/" -f 10 | cut -d "_" -f 2 | cut -d "." -f1`
      echo $number
      root -l -b -q -x ChangeStructureToStandardCalo.C\(\"$OUTPUTDIR_LHC13d2_A/GammaCalo_$number.root\"\,\"$OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2_$number.root\"\,\"GammaCalo_$number\"\)
      root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2_$number.root\"\,\"$OUTPUTDIR/CutSelectionCalo_LHC13d2_AOD_$number.log\"\)

   done;
   
   ls $OUTPUTDIR_LHC13d2b_A/GammaCalo_*.root > fileLHC13d2b.txt
   fileNumbersb=`cat fileLHC13d2b.txt`
   for fileName in $fileNumbersb; do
      echo $fileName
      number=`echo $fileName  | cut -d "/" -f 10 | cut -d "_" -f 2 | cut -d "." -f1`
      echo $number
      root -l -b -q -x ChangeStructureToStandardCalo.C\(\"$OUTPUTDIR_LHC13d2b_A/GammaCalo_$number.root\"\,\"$OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2b_$number.root\"\,\"GammaCalo_$number\"\)
      root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2b_$number.root\"\,\"$OUTPUTDIR/CutSelectionCalo_LHC13d2b_AOD_$number.log\"\)
   done;
   
   rm $OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2_LHC13d2b_*.root
   ls $OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2_*.root > filesForMerging.txt
   filesForMerging=`cat filesForMerging.txt`
   for fileName in $filesForMerging; do
      echo $fileName
      number=`echo $fileName  | cut -d "/" -f 9 | cut -d "_" -f 7 | cut -d "." -f1`
      echo $number
      if [ -f $OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2_$number.root ] && [ -f $OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2b_$number.root ] ; then
         hadd -f $OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2_LHC13d2b_$number.root $OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2_$number.root $OUTPUTDIR/GammaCalo_GA_PbPb_MC_AOD_LHC13d2b_$number.root 
      fi
   done
   
   
else 
   # all good runs according to RCT
   ls $OUTPUTDIR_LHC13d2_A/GammaCalo_*.root > fileLHC13d2.txt
   fileNumbers=`cat fileLHC13d2.txt`
   for fileName in $fileNumbers; do
      echo $fileName
      number=`echo $fileName  | cut -d "/" -f 10 | cut -d "_" -f 2 | cut -d "." -f1`
      echo $number
      root -l -b -q -x ChangeStructureToStandardCalo.C\(\"$OUTPUTDIR_LHC13d2_A/GammaCalo_$number.root\"\,\"$OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2_$number.root\"\,\"GammaCalo_$number\"\)
      root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2_$number.root\"\,\"$OUTPUTDIR/CutSelectionCalo_LHC13d2_$number.log\"\)

   done;
   
   ls $OUTPUTDIR_LHC13d2b_A/GammaCalo_*.root > fileLHC13d2b.txt
   fileNumbersb=`cat fileLHC13d2b.txt`
   for fileName in $fileNumbersb; do
      echo $fileName
      number=`echo $fileName  | cut -d "/" -f 10 | cut -d "_" -f 2 | cut -d "." -f1`
      echo $number
      root -l -b -q -x ChangeStructureToStandardCalo.C\(\"$OUTPUTDIR_LHC13d2b_A/GammaCalo_$number.root\"\,\"$OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2b_$number.root\"\,\"GammaCalo_$number\"\)
      root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2b_$number.root\"\,\"$OUTPUTDIR/CutSelectionCalo_LHC13d2b_$number.log\"\)
   done;
   
   
   rm $OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2_LHC13d2b_*.root
   ls $OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2_*.root > filesForMerging.txt
   filesForMerging=`cat filesForMerging.txt`
   for fileName in $filesForMerging; do
      echo $fileName
      number=`echo $fileName  | cut -d "/" -f 9 | cut -d "_" -f 6 | cut -d "." -f1`
      echo $number
      if [ -f $OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2_$number.root ] && [ -f $OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2b_$number.root ] ; then
         hadd -f $OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2_LHC13d2b_$number.root $OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2_$number.root $OUTPUTDIR/GammaCalo_GA_PbPb_MC_LHC13d2b_$number.root 
      fi
   done
   
fi


if [ $2 = "AODdata" ]; then
   ls $OUTPUTDIR_LHC10h_A/GammaCalo_*.root > fileLHC10h.txt
   fileNumbersData=`cat fileLHC10h.txt`
   for fileName in $fileNumbersData; do
      echo $fileName
      number=`echo $fileName  | cut -d "/" -f 10 | cut -d "_" -f 2 | cut -d "." -f1`
      echo $number
      root -l -b -q -x ChangeStructureToStandardCalo.C\(\"$OUTPUTDIR_LHC10h_A/GammaCalo_$number.root\"\,\"$OUTPUTDIR/GammaCalo_GA_PbPb_LHC10h-pass2_$number.root\"\,\"GammaCalo_$number\"\)
      root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_GA_PbPb_LHC10h-pass2_$number.root\"\,\"$OUTPUTDIR/CutSelectionCalo_LHC10h_$number.log\"\)
   done;   
else 
   ls $OUTPUTDIR_LHC10h_A/GammaCalo_*.root > fileLHC10h.txt
   fileNumbersData=`cat fileLHC10h.txt`
   for fileName in $fileNumbersData; do
      echo $fileName
      number=`echo $fileName  | cut -d "/" -f 10 | cut -d "_" -f 2 | cut -d "." -f1`
      echo $number
      root -l -b -q -x ChangeStructureToStandardCalo.C\(\"$OUTPUTDIR_LHC10h_A/GammaCalo_$number.root\"\,\"$OUTPUTDIR/GammaCalo_GA_PbPb_LHC10h-pass2_$number.root\"\,\"GammaCalo_$number\"\)
      root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_GA_PbPb_LHC10h-pass2_$number.root\"\,\"$OUTPUTDIR/CutSelectionCalo_LHC10h_$number.log\"\)
   done;
fi   
