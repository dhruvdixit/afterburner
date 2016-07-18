#! /bin/bash

BASEDIR=/home/admin1/leardini/GridOutput/PbPb
TRAINDIR=Legotrain-vAN-20150601;
OUTPUTDIR=$BASEDIR/$TRAINDIR;
OUTPUTDIRout=$BASEDIR/$TRAINDIR/NotFlatCent;
mkdir -p $OUTPUTDIRout
# OUTPUTDIRold=$BASEDIR/Legotrain-vAN-20150507;
# OUTPUTDIRFlat=$OUTPUTDIRold/fileCentFlat;  #$BASEDIR/$TRAINDIR/fileCentFlat;


LHC11hData=153_20150602-1241; #151_20150602-1119; #
LHC11hDataPhi=154_20150602-1241; #152_20150602-1120; #

LHC14a1awithEta=357_20150602-1122; #
LHC14a1bwithEta=359_20150602-1244; #

LHC14a1awithPi0=358_20150602-1244; #
LHC14a1bwithPi0=360_20150602-1123; #

standardData=162;
standardPhiData=164;
standard=162;
standardPhi=164; 
added=163;
addedPhi=165;

#if [ $1 = "AODdata" ]; then
#   TRAINPATHData=GA_PbPb_AOD
#else
#   TRAINPATHData=GA_PbPb
#fi  
#OUTPUTDIR_LHC11h=$BASEDIR/$TRAINDIR/$TRAINPATHData-$LHC11hData

#if [ $2 = "AODmc" ]; then
#   TRAINPATHMC=GA_PbPb_MC_AOD
#else
#   TRAINPATHMC=GA_PbPb_MC
#fi  
#OUTPUTDIR_LHC14a1a=$BASEDIR/$TRAINDIR/$TRAINPATHMC-$LHC14a1a
#OUTPUTDIR_LHC14a1b=$BASEDIR/$TRAINDIR/$TRAINPATHMC-$LHC14a1b

###################################### LHC14a1a

hadd $OUTPUTDIRout/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1a_$standard.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1awithEta/merge_runlist_6/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1a_$standard.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1awithPi0/merge_runlist_7/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1a_$standardPhi.root

hadd $OUTPUTDIRout/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1a_Eta_$added.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1awithEta/merge_runlist_6/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1a_$added.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1awithEta/merge_runlist_7/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1a_$addedPhi.root

hadd $OUTPUTDIRout/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1a_Pi0_$added.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1awithPi0/merge_runlist_6/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1a_$added.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1awithPi0/merge_runlist_7/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1a_$addedPhi.root


####################################### LHC14a1b
hadd $OUTPUTDIRout/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1b_$standard.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1bwithEta/merge_runlist_6/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1b_$standard.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1bwithPi0/merge_runlist_7/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1b_$standardPhi.root

hadd $OUTPUTDIRout/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1b_Eta_$added.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1bwithEta/merge_runlist_6/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1b_$added.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1bwithEta/merge_runlist_7/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1b_$addedPhi.root

hadd $OUTPUTDIRout/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1b_Pi0_$added.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1bwithPi0/merge_runlist_6/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1b_$added.root $OUTPUTDIR/GA_PbPb_MC_AOD-$LHC14a1bwithPi0/merge_runlist_7/GammaConvV1_GA_PbPb_MC_AOD_LHC14a1b_$addedPhi.root


###########################################   DATA   ###########################################   

hadd $OUTPUTDIRout/GammaConvV1_GA_PbPb_LHC11h-pass2_162.root $OUTPUTDIR/GA_PbPb_AOD-$LHC11hData/merge_runlist_7/GammaConvV1_GA_PbPb_LHC11h-pass2_$standardData.root $OUTPUTDIR/GA_PbPb_AOD-$LHC11hDataPhi/merge/GammaConvV1_GA_PbPb_LHC11h-pass2_$standardPhiData.root

