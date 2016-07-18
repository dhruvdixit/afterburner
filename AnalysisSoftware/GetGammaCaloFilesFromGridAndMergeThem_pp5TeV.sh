#! /bin/bash
#This file has added the 15n parts
#
function CopyFileIfNonExisitent()
{
    if [ -f $1/root_archive.zip ] && [ -s $1/root_archive.zip ]; then 
        echo "$1/root_archive.zip exists";
    else     
        mkdir -p $1
        alien_cp alien:$2/root_archive.zip file:$1/
    fi    
    unzip -u $1/root_archive.zip -d $1/
}

function ChangeStructureIfNeeded()
{
    if [ -f $2 ]; then 
        echo "already changed"
    else
        root -l -b -q -x ChangeStructureToStandardCalo.C\(\"$1\"\,\"$2\"\,\"GammaCalo_$3\"\)
    fi    
}

# copies files from grid
# creates directory
# changes internal structure

# switches to enable/disable certain procedures
DOWNLOADON=1
MERGEON=1
MERGEONBINSSingle=1
MERGEONBINS=1

# check if train configuration has actually been given
HAVELHC11a=1
HAVELHC12f1a=1
HAVELHC12f1b=1
HAVELHC12i3=1
HAVELHC15g1a=1
HAVELHC13g=1
HAVELHC15g2=1
HAVELHC15a3a=1
HAVELHC15a3aplus=1
HAVELHC15n=1 #My addtion for 15n

# default trainconfigurations
LHC11aData="";
LHC12f1aMC="";
LHC12f1bMC="";
LHC12i3MC="";
LHC15g1aMC="";
LHC13gData="";
LHC15a3aMC=""; 
LHC15a3aplusMC=""; 
LHC15g2MC=""; 
LHC15nData="1";#My addtion for 15n


NSlashes=10
NSlashes2=9

if[ $1 = "ddixit" ]; then
    BASEDIR=/home/dhruv/LegoTrainsOutPuts/pp
elif [ $1 = "fbock" ]; then 
    BASEDIR=/mnt/additionalStorage/OutputLegoTrains/pp
    NSlashes=8
    NSlashes2=7
elif [ $1 = "fbockGSI" ]; then 
    BASEDIR=/hera/alice/fbock/Grid/OutputLegoTrains/pp
elif [ $1 = "leardini" ]; then 
    BASEDIR=/Users/lucy/
elif [ $1 = "leardiniALICESERV1" ]; then 
    BASEDIR=/alidata50/alice_u/leardini/GridOutput/PbPb/
elif [ $1 = "leardiniGSI" ]; then 
    BASEDIR=/hera/alice/leardini/Grid/OutputLegoTrains/pp
elif [ $1 = "passfeld" ]; then 
    BASEDIR=~/work/Gridoutput/pp
elif [ $1 = "passfeldMAF" ]; then 
    BASEDIR=/data9/a_pass02/gamma_test/AnalysisSoftware/LegoTrain/
elif [ $1 = "passfeldGSI" ]; then  
    BASEDIR=/hera/alice/passfeld/Grid/OutputLegoTrains/pp
elif [ $1 = "amarin" ]; then     
    BASEDIR=/Users/marin/
elif [ $1 = "amarinGSI" ]; then     
    BASEDIR=/hera/alice/marin/Grid/OutputLegoTrains/pp 
elif [ $1 = "amarinALICESERV1" ]; then     
    BASEDIR=/alidata50/alice_u/amarin/GridOutput/PbPb/   
elif [ $1 = "mwilde" ]; then        
    BASEDIR=~/work/GridOutput 
elif [ $1 = "mwildeGSI" ]; then           
    BASEDIR=/hera/alice/mwilde/Grid/OutputLegoTrains/pp 
elif [ $1 = "pgonzales" ]; then     
    BASEDIR=~/work/GridOutput 
elif [ $1 = "pgonzalesGSI" ]; then        
    BASEDIR=/hera/alice/pgonzales/Grid/OutputLegoTrains/pp
elif [ $1 = "dmuhlhei" ]; then
    BASEDIR=~/data/work/Grid
    NSlashes=9
    NSlashes2=8
elif [ $1 = "bsahlmul" ]; then
    BASEDIR=/Users/sahlmul/Documents/ALICE/mycode/AnalysisSoftware/grid
    NSlashes=11
    NSlashes2=10
fi

# TRAINDIR=Legotrain-Calo-LHC11a-example
# LHC11aData="1009"; #2,15
# LHC12f1aMC="1182"; #2,15
# LHC12f1bMC="1183"; #2,15
# LHC12i3MC="1184"; # 2,15
# LHC15g1aMC="1180";  #2, 15

# TRAINDIR=Legotrain-Calo-LHC13g-example
# LHC13gData="959"; # 42,55,69,82
# LHC15a3aMC="1186";  # 42,55
# LHC15a3aplusMC="1185";  # 42,55,69,82
# LHC15g2MC="1187"; # 42,55,69,82

# TRAINDIR=Legotrain-vAN-20151025-MultiplicityDependence
# # LHC11aData="371";
# LHC12f1aMC="1258"; #calo98, convCalo98
# LHC12f1bMC="1259"; #calo98, convCalo98
# LHC15g1aMC="1262"; #calo98, convCalo98
# 
# LHC15a3aMC="1260"; 
# LHC15a3aplusMC="1261"; 
# # LHC15g2MC="1263"; 
# # LHC15g2MC="1264"; 

# TRAINDIR=Legotrain-vAN-20151103-MultiplicityDependence2
# # LHC11aData="371";
# LHC12f1aMC="1273"; #calo98, convCalo98
# LHC12f1bMC="1274"; #calo98, convCalo98
# LHC15g1aMC="1275"; #calo98, convCalo98

# LHC15a3aMC="1260"; 
# LHC15a3aplusMC="1261"; 
# LHC15g2MC="1263"; 
# LHC15g2MC="1264"; 

# TRAINDIR=Legotrain-vAN-20151106-MultiplicityDependence3
# # LHC11aData="371";
# LHC12f1aMC="1291"; 
# LHC12f1bMC="1292"; 
# # LHC15g1aMC="1275"; 

# TRAINDIR=Legotrain-vAN-20151101-NonLinearityStudies
# LHC11aData="1059";
# LHC12f1aMC="1270"; 
# LHC12f1bMC="1271"; 


# TRAINDIR=Legotrain-Calo-LHC13g-Sys
# LHC13gData="1079"
# LHC15a3aMC="1249"; 
# LHC15a3aMC="1232";
# LHC15a3aplusMC="1236"; 
# LHC15a3aMC="1233";
# LHC15a3aplusMC="1237"; 
# LHC15a3aMC="1234";
# LHC15a3aplusMC="1238"; 
# LHC15a3aMC="1235";
# LHC15a3aplusMC="1239"; 

# TRAINDIR=Legotrain-vAN-20151213-ReprodJason
# LHC11aData="1124";
# LHC12f1aMC="1358"; 
# LHC12f1bMC="1359"; 

# TRAINDIR=Legotrain-vAN-20151213-CalibDefaultTiming
# LHC11aData="1125";
# LHC12f1aMC="1360"; 
# LHC12f1bMC="1361"; 
# LHC15g1aMC="1388";
# LHC12i3MC="1385";
# 
# LHC13gData="1126"
# LHC15g2MC="1362";

# TRAINDIR=Legotrain-vAN-20151213-CalibOpenTiming
# LHC11aData="1127";
# LHC12f1aMC="1360"; 
# LHC12f1bMC="1361"; 
# 
# LHC13gData="1128"
# LHC15g2MC="1362";

# TRAINDIR=Legotrain-vAN-20151213-CalibOpenTimingDeltaT
# LHC11aData="1129";
# LHC12f1aMC="1360"; 
# LHC12f1bMC="1361"; 
# 
# LHC13gData="1130"
# LHC15g2MC="1362";

# TRAINDIR=Legotrain-vAN-20151218-TriggersWithoutPileupAndPCMTriggers
# LHC13gData="1136"
# LHC15g2MC="1373";
# LHC15a3aMC="1377"; 
# LHC15a3aplusMC="1375"; 
# LHC11aData="1135";
# LHC12f1aMC="1371"; 
# LHC12f1bMC="1372"; 
# LHC15g1aMC="1379"; 

# TRAINDIR=Legotrain-vAN-20160108-CalibOpenTiming
# LHC11aData="1169";
# LHC12f1aMC="1467"; 
# LHC12f1bMC="1468"; 
# LHC15g1aMC="1470";
# LHC12i3MC="1469";
# 
# LHC13gData="1170"
# LHC15g2MC="1475";
# LHC15a3aMC="1472"; 
# LHC15a3aplusMC="1473"; 

# TRAINDIR=Legotrain-vAN-20160108-CalibOpenTimingDeltaT
# LHC11aData="1171";
# LHC12f1aMC="1467"; 
# LHC12f1bMC="1468"; 
# LHC15g1aMC="1470";
# LHC12i3MC="1469";

# LHC13gData="1172"
# LHC15g2MC="1475";
# LHC15a3aMC="1472"; 
# LHC15a3aplusMC="1473"; 

# TRAINDIR=Legotrain-vAN-20160124-NLCorrV1
# # LHC11aData="1177";
# LHC12f1aMC="1519"; 
# LHC12f1bMC="1520"; 
# LHC12i3MC="1521";
# LHC15g1aMC="1522";

# LHC13gData="1196"
# LHC15g2MC="1523";
# LHC15a3aMC="1524"; 
# LHC15a3aMC="1532"; 
# LHC15a3aplusMC="1525"; 
# LHC15a3aplusMC="1534"; 
# LHC15a3aMC="LHC15a3a"; 
# LHC15a3aplusMC="LHC15a3aplus"; 

# TRAINDIR=Legotrain-vAN-20160129-NLCorrV2
# LHC11aData="1205";
# LHC12f1aMC="1552"; 
# LHC12f1bMC="1553"; 
# LHC12i3MC="1554";
# LHC15g1aMC="1555";
# 
# LHC13gData="1206"
# LHC15g2MC="1556";
# LHC15a3aMC="1558"; 
# # LHC15a3aMC="1532"; 
# LHC15a3aplusMC="1560"; 
# # LHC15a3aplusMC="1534"; 

# TRAINDIR=Legotrain-SysAdd-Calo
# LHC11aData="1208";
# LHC11aData="1224";
# LHC11aData="1239";
# LHC11aData="1259";
# LHC12f1aMC="1573"; 
# LHC12f1bMC="1574"; 
# LHC12f1aMC="1562"; 
# LHC12f1bMC="1563"; 
# LHC15g1aMC="1564";
# LHC15g1aMC="1592";

# LHC13gData="1211"
# LHC13gData="1212"
# LHC13gData="1213"
# LHC15g2MC="1571";
# LHC15g2MC="1572"
# LHC15a3aMC="1565"; 
# LHC15a3aplusMC="1568"; 
# LHC15a3aMC="1566"; 
# LHC15a3aplusMC="1569"; 
# LHC15a3aMC="1567"; 
# LHC15a3aplusMC="1570"; 
# LHC15a3aMC="1593"; 
# LHC15a3aplusMC="1594"; 

# TRAINDIR=Legotrain-SysAdd-Time100ns
# LHC11aData="1218";
# LHC13gData="1220"

# TRAINDIR=Legotrain-SysAdd-Time200ns
# LHC11aData="1219";
# LHC13gData="1221"

# TRAINDIR=Legotrain-SysAdd-Calo2
# LHC11aData="1261";
# LHC15g1aMC="1649";

# LHC13gData="1275"
# LHC15a3aMC="1642"; 
# LHC15a3aplusMC="1645"; 

# LHC13gData="1276"
# LHC15a3aMC="1643"; 
# LHC15a3aplusMC="1646"; 

# LHC13gData="1274"
# LHC15a3aMC="1650"; 
# LHC15a3aplusMC="1644"; 

# LHC13gData="1262"
# LHC15g2MC="1653";
# LHC15g2MC="1647";
# LHC15g2MC="1648";
# LHC15a3aMC="1651"; 
# LHC15a3aplusMC="1652"; 

TRAINDIR=Legotrain_LHC15n_pass1
LHC15g1aMC="1661";

LHC15a3aMC="1659"; 
LHC15a3aplusMC="1660"; 



OUTPUTDIR=$BASEDIR/$TRAINDIR

echo "************************************************************************************************";
echo "Directory to be writen into " $OUTPUTDIR
echo "************************************************************************************************";
echo ""
echo ""

if [$2 = "LHC15n" ]; then
    echo "************************************************************************************************";
    echo "********************************* Copying LHC15n ***********************************************";
    echo "************************************************************************************************";
    if [ "$HAVELHC15n" == 1]; then
	LHC15nData= `alice/cern.ch/user/a/alitrain/PWGGA/GA_pp/1522_20160422-1712/merge`

if [ $2 = "LHC11a" ]; then 
    echo "************************************************************************************************";
    echo "********************************* Copying LHC11a ***********************************************";
    echo "************************************************************************************************";

    if [ "$LHC11aData" == "" ]; then 
        HAVELHC11a=0;
    fi
    if [ "$LHC12f1aMC" = "" ]; then 
        HAVELHC12f1a=0; 
    fi
    if [ "$LHC12f1bMC" = "" ]; then 
        HAVELHC12f1b=0; 
    fi
    if [ "$LHC12i3MC" = "" ]; then 
        HAVELHC12i3=0; 
    fi
    if [ "$LHC15g1aMC" = "" ]; then 
        HAVELHC15g1a=0; 
    fi

    if [ $HAVELHC11a == 1 ]; then
        LHC11aData=`alien_ls /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp/ | grep $LHC11aData\_`
        if [ "$LHC11aData" == "" ]; then
            HAVELHC11a=0;
        else 
            OUTPUTDIR_LHC11a=$BASEDIR/$TRAINDIR/GA_pp-$LHC11aData
        fi
    fi
    
    if [ $HAVELHC12f1a == 1 ]; then
        LHC12f1aMC=`alien_ls /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/ | grep $LHC12f1aMC\_`
        if [ "$LHC12f1aMC" == "" ]; then
            HAVELHC12f1a=0;
        else 
            OUTPUTDIR_LHC12f1a=$BASEDIR/$TRAINDIR/GA_pp_MC-$LHC12f1aMC
        fi    
    fi  
    
    if [ $HAVELHC12f1b == 1 ]; then
        LHC12f1bMC=`alien_ls /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/ | grep $LHC12f1bMC\_`
        if [ "$LHC12f1bMC" == "" ]; then
            HAVELHC12f1b=0;
        else 
            OUTPUTDIR_LHC12f1b=$BASEDIR/$TRAINDIR/GA_pp_MC-$LHC12f1bMC
        fi    
    fi
    
    if [ $HAVELHC12i3 == 1 ]; then
        LHC12i3MC=`alien_ls /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/ | grep $LHC12i3MC\_`
        if [ "$LHC12i3MC" == "" ]; then
            HAVELHC12i3=0;
        else 
            OUTPUTDIR_LHC12i3=$BASEDIR/$TRAINDIR/GA_pp_MC-$LHC12i3MC
        fi
    fi
    if [ $HAVELHC15g1a == 1 ]; then
        LHC15g1aMC=`alien_ls /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/ | grep $LHC15g1aMC\_`
        if [ "$LHC15g1aMC" == "" ]; then
            HAVELHC15g1a=0;
        else 
            OUTPUTDIR_LHC15g1a=$BASEDIR/$TRAINDIR/GA_pp_MC-$LHC15g1aMC
        fi
    fi

    if [ $DOWNLOADON == 1 ]; then
	if [ $HAVELHC11a == 1 ]; then
            echo "downloading LHC11a"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC11a "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp/$LHC11aData/merge_runlist_1"
        fi    
        if [ $HAVELHC11a == 1 ]; then
            echo "downloading LHC11a"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC11a "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp/$LHC11aData/merge_runlist_1"
        fi    
        if [ $HAVELHC12f1a == 1 ]; then
            echo "downloading LHC12f1a"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC12f1a "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/$LHC12f1aMC/merge_runlist_1"
        fi    
        if [ $HAVELHC12f1b == 1 ]; then
            echo "downloading LHC12f1b"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC12f1b "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/$LHC12f1bMC/merge_runlist_1"
        fi    
        if [ $HAVELHC12i3 == 1 ]; then
            echo "LHC12i3"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC12i3 "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/$LHC12i3MC/merge_runlist_1"
        fi
        if [ $HAVELHC15g1a == 1 ]; then
            echo "LHC15g1a"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC15g1a "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/$LHC15g1aMC/merge"
            
            echo "copying LHC11aJetJet" 
            runNumbers=`cat runNumbersLHC11aJetJet.txt`
            echo $runNumbers
            for runNumber in $runNumbers; do
                echo $runNumber
                binNumbersJJ=`cat binNumbersJJToMerge.txt`
                for binNumber in $binNumbersJJ; do
                    echo $binNumber
                    CopyFileIfNonExisitent $OUTPUTDIR_LHC15g1a/$binNumber/$runNumber "/alice/sim/2015/LHC15g1a/$binNumber/$runNumber/PWGGA/GA_pp_MC/$LHC15g1aMC"
                done;   
            done;
        fi    
    fi
    
    if [ $HAVELHC11a == 1 ]; then
        ls $OUTPUTDIR_LHC11a/GammaCalo_*.root > fileLHC11a.txt
        fileNumbers=`cat fileLHC11a.txt`
        for fileName in $fileNumbers; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
            echo $number
            ChangeStructureIfNeeded $OUTPUTDIR_LHC11a/GammaCalo_$number.root $OUTPUTDIR/GammaCalo_LHC11a-pass4_$number.root $number
            root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_LHC11a-pass4_$number.root\"\,\"$OUTPUTDIR/CutSelection_GammaCalo_LHC11a_$number.log\"\)
        done;
    fi
    
    if [ $HAVELHC12f1a == 1 ]; then
        ls $OUTPUTDIR_LHC12f1a/GammaCalo_*.root > fileLHC12f1a.txt
        fileNumbers=`cat fileLHC12f1a.txt`
        for fileName in $fileNumbers; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
            echo $number
            ChangeStructureIfNeeded $OUTPUTDIR_LHC12f1a/GammaCalo_$number.root $OUTPUTDIR/GammaCalo_MC_LHC12f1a_$number.root $number
            root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_MC_LHC12f1a_$number.root\"\,\"$OUTPUTDIR/CutSelection_GammaCalo_MC_LHC12f1a_$number.log\"\)
        done;
    fi
    
    if [ $HAVELHC12f1b == 1 ]; then
        ls $OUTPUTDIR_LHC12f1b/GammaCalo_*.root > fileLHC12f1b.txt
        fileNumbers=`cat fileLHC12f1b.txt`
        for fileName in $fileNumbers; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
            echo $number
            ChangeStructureIfNeeded $OUTPUTDIR_LHC12f1b/GammaCalo_$number.root $OUTPUTDIR/GammaCalo_MC_LHC12f1b_$number.root $number
            root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_MC_LHC12f1b_$number.root\"\,\"$OUTPUTDIR/CutSelection_GammaCalo_MC_LHC12f1b_$number.log\"\)
        done;
    fi
    
    if [ $HAVELHC12i3 == 1 ]; then
        ls $OUTPUTDIR_LHC12i3/GammaCalo_*.root > fileLHC12i3.txt
        fileNumbers=`cat fileLHC12i3.txt`
        for fileName in $fileNumbers; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
            echo $number
            ChangeStructureIfNeeded $OUTPUTDIR_LHC12i3/GammaCalo_$number.root $OUTPUTDIR/GammaCalo_MC_LHC12i3_$number.root $number
            root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_MC_LHC12i3_$number.root\"\,\"$OUTPUTDIR/CutSelection_GammaCalo_MC_LHC12i3_$number.log\"\)
        done;
    fi

    if [ $HAVELHC15g1a == 1 ]; then     
        ls $OUTPUTDIR_LHC15g1a/GammaCalo_*.root > fileLHC15g1a.txt
        fileNumbers=`cat fileLHC15g1a.txt`
        for fileName in $fileNumbers; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
            echo $number
            ChangeStructureIfNeeded $OUTPUTDIR_LHC15g1a/GammaCalo_$number.root $OUTPUTDIR/GammaCalo_MC_LHC15g1a_$number.root $number
            root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_MC_LHC15g1a_$number.root\"\,\"$OUTPUTDIR/CutSelection_GammaCalo_MC_LHC15g1a_$number.log\"\)
        done;

        if [ $MERGEONBINSSingle = 1 ]; then
            binNumbersJJ=`cat binNumbersJJToMerge.txt`
            echo $binNumbersJJ
            ls $OUTPUTDIR_LHC15g1a/GammaCalo_*.root > filetemp.txt
            mkdir -p $OUTPUTDIR/LHC15g1aFineBins
            for binNumber in $binNumbersJJ; do
                echo $binNumber
                fileNumbers=`cat filetemp.txt`
                for fileName in $fileNumbers; do
                    echo $fileName
                    number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
                    echo $number
                    hadd -f $OUTPUTDIR_LHC15g1a/$binNumber/GammaCalo_$number.root $OUTPUTDIR_LHC15g1a/$binNumber/*/GammaCalo_$number.root
                    ChangeStructureIfNeeded $OUTPUTDIR_LHC15g1a/$binNumber/GammaCalo_$number.root $OUTPUTDIR/LHC15g1aFineBins/GammaCalo_MC_LHC15g1a$binNumber\_$number.root $number
                done;
            done;
        fi    
    fi
    
    if [ $MERGEON == 1 ]; then
        rm $OUTPUTDIR/GammaCalo_MC_LHC12f1a_LHC12f1b_*.root
        ls $OUTPUTDIR/GammaCalo_MC_LHC12f1a_*.root > filesForMerging.txt
        filesForMerging=`cat filesForMerging.txt`
        for fileName in $filesForMerging; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes2 | cut -d "_" -f 4 | cut -d "." -f1`
        filesForMerging=`cat filesForMerging.txt`
            echo $number
            if [ -f $OUTPUTDIR/GammaCalo_MC_LHC12f1a_$number.root ] && [ -f $OUTPUTDIR/GammaCalo_MC_LHC12f1b_$number.root ] ; then
                hadd -f $OUTPUTDIR/GammaCalo_MC_LHC12f1a_LHC12f1b_$number.root $OUTPUTDIR/GammaCalo_MC_LHC12f1a_$number.root $OUTPUTDIR/GammaCalo_MC_LHC12f1b_$number.root
            fi
        done
        
        ls $OUTPUTDIR/GammaCalo_MC_LHC12f1a_*.root > filesForMerging.txt
        for fileName in $filesForMerging; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes2 | cut -d "_" -f 4 | cut -d "." -f1`
            echo $number
            if [ -f $OUTPUTDIR/GammaCalo_MC_LHC12f1a_$number.root ] && [ -f $OUTPUTDIR/GammaCalo_MC_LHC12i3_$number.root ] ; then
                hadd -f $OUTPUTDIR/GammaCalo_MC_LHC12f1a_LHC12i3_$number.root $OUTPUTDIR/GammaCalo_MC_LHC12i3_$number.root $OUTPUTDIR/GammaCalo_MC_LHC12f1a_$number.root
            fi
        done
        
        
        ls $OUTPUTDIR/GammaCalo_MC_LHC12f1a_LHC12f1b_*.root > filesForMerging.txt
        filesForMerging=`cat filesForMerging.txt`
        for fileName in $filesForMerging; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes2 | cut -d "_" -f 5 | cut -d "." -f1`
            echo $number
            if [ -f $OUTPUTDIR/GammaCalo_MC_LHC12f1a_LHC12f1b_$number.root ] && [ -f $OUTPUTDIR/GammaCalo_MC_LHC12i3_$number.root ] ; then
                hadd -f $OUTPUTDIR/GammaCalo_MC_LHC12f1a_LHC12f1b_LHC12i3_$number.root $OUTPUTDIR/GammaCalo_MC_LHC12f1a_LHC12f1b_$number.root $OUTPUTDIR/GammaCalo_MC_LHC12i3_$number.root
            fi
        done
    fi
    
    ls $OUTPUTDIR/GammaCalo_MC_LHC15g1a_*.root > filesForMerging.txt
    filesForMerging=`cat filesForMerging.txt`
    if [ $MERGEONBINS == 1 ]; then    
        for fileName in $filesForMerging; do
            binsForMerging=`cat binNumbersJJToMerge.txt`
            number=`echo $fileName  | cut -d "/" -f $NSlashes2 | cut -d "_" -f 4 | cut -d "." -f1`
            TOMERGE="";
            for bin in $binsForMerging; do
                echo $OUTPUTDIR/LHC15g1aFineBins/GammaCalo_MC_LHC15g1a$bin\_$number.root
                if [ -f $OUTPUTDIR/LHC15g1aFineBins/GammaCalo_MC_LHC15g1a$bin\_$number.root ]; then
                    TOMERGE="$TOMERGE $OUTPUTDIR/LHC15g1aFineBins/GammaCalo_MC_LHC15g1a$bin"
                    TOMERGE+="_$number.root"
                else 
                    echo "I couldn't find the file for bin $bin, number $number, $OUTPUTDIR/LHC15g1aFineBins/GammaCalo_MC_LHC15g1a$bin\_$number.root";
                fi
            done;
            hadd -f $OUTPUTDIR/GammaCalo_MC_LHC15g1aFinerPtHardBins_$number.root $TOMERGE
        done;
    fi

elif [ $2 = "LHC13g" ]; then 
    
    if [ "$LHC13gData" == "" ]; then 
        HAVELHC13g=0;
    fi
    
    if [ "$LHC15a3aMC" == "" ]; then 
        HAVELHC15a3a=0;
    fi

    if [ "$LHC15a3aplusMC" == "" ]; then 
        HAVELHC15a3aplus=0;
    fi
    
    if [ "$LHC15g2MC" == "" ]; then 
        HAVELHC15g2=0;
    fi

    if [ $HAVELHC13g == 1 ]; then
        LHC13gData=`alien_ls /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp/ | grep $LHC13gData\_`
        if [ "$LHC13gData" == "" ]; then
            HAVELHC13g=0;
        else 
            OUTPUTDIR_LHC13g=$BASEDIR/$TRAINDIR/GA_pp-$LHC13gData
        fi
    fi

    if [ $HAVELHC15g2 == 1 ]; then
        LHC15g2MC=`alien_ls /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/ | grep $LHC15g2MC\_`
        echo $LHC15g2MC "   -> full dir"
        if [ "$LHC15g2MC" == "" ]; then
            HAVELHC15g2=0;
        else 
            OUTPUTDIR_LHC15g2=$BASEDIR/$TRAINDIR/GA_pp_MC-$LHC15g2MC
        fi
    fi
    
    if [ $HAVELHC15a3a == 1 ]; then
        LHC15a3aMC=`alien_ls /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/ | grep $LHC15a3aMC\_`
        if [ "$LHC15a3aMC" == "" ]; then
            HAVELHC15a3a=0;
        else 
            OUTPUTDIR_LHC15a3a=$BASEDIR/$TRAINDIR/GA_pp_MC-$LHC15a3aMC
        fi   
    fi

    if [ $HAVELHC15a3aplus == 1 ]; then
        LHC15a3aplusMC=`alien_ls /alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/ | grep $LHC15a3aplusMC\_`
        if [ "$LHC15a3aplusMC" == "" ]; then
            HAVELHC15a3aplus=0;
        else 
            OUTPUTDIR_LHC15a3aplus=$BASEDIR/$TRAINDIR/GA_pp_MC-$LHC15a3aplusMC
        fi    
    fi
    
    if [ $DOWNLOADON == 1 ]; then
        if [ $HAVELHC13g == 1 ]; then
            echo "downloading LHC13g"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC13g "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp/$LHC13gData/merge"
        fi
        
        if [ $HAVELHC15g2 == 1 ]; then
            echo "downloading LHC15g2"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC15g2 "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/$LHC15g2MC/merge"
        fi    

        if [ $HAVELHC15a3a == 1 ]; then
            echo "downloading LHC15a3a"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC15a3a "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/$LHC15a3aMC/merge"
        fi
        
        if [ $HAVELHC15a3aplus == 1 ]; then
            echo "downloading LHC15a3a_plus"
            CopyFileIfNonExisitent $OUTPUTDIR_LHC15a3aplus "/alice/cern.ch/user/a/alitrain/PWGGA/GA_pp_MC/$LHC15a3aplusMC/merge"
        fi
        
        echo "copying LHC13gJetJet in bins" 
        runNumbers=`cat runNumbersLHC13gJetJet.txt`
        echo $runNumbers
        for runNumber in $runNumbers; do
            echo $runNumber
            binNumbersJJ=`cat binNumbersJJToMerge.txt`
            if [ $DOWNLOADON = 1 ]; then
                for binNumber in $binNumbersJJ; do
                    echo $binNumber
                    if [ $HAVELHC15a3a == 1 ]; then
                        CopyFileIfNonExisitent $OUTPUTDIR_LHC15a3a/$binNumber/$runNumber "/alice/sim/2015/LHC15a3a/$binNumber/$runNumber/PWGGA/GA_pp_MC/$LHC15a3aMC"
                    fi
                    if [ $HAVELHC15a3aplus == 1 ]; then
                        mkdir -p $OUTPUTDIR_LHC15a3aplus/$binNumber/$runNumber
                        CopyFileIfNonExisitent $OUTPUTDIR_LHC15a3aplus/$binNumber/$runNumber "/alice/sim/2015/LHC15a3a_plus/$binNumber/$runNumber/PWGGA/GA_pp_MC/$LHC15a3aplusMC"
                    fi    
                done;   
            fi  
        done;
    fi 
    
    if [ $HAVELHC13g == 1 ]; then
        ls $OUTPUTDIR_LHC13g/GammaCalo_*.root > fileLHC13g.txt
        fileNumbers=`cat fileLHC13g.txt`
        for fileName in $fileNumbers; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
            echo $number
            ChangeStructureIfNeeded $OUTPUTDIR_LHC13g/GammaCalo_$number.root $OUTPUTDIR/GammaCalo_LHC13g-pass1_$number.root $number
            root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_LHC13g-pass1_$number.root\"\,\"$OUTPUTDIR/CutSelection_GammaCalo_LHC13g_$number.log\"\)
        done;
    fi

    if [ $HAVELHC15g2 == 1 ]; then
        ls $OUTPUTDIR_LHC15g2/GammaCalo_*.root > fileLHC15g2.txt
        fileNumbers=`cat fileLHC15g2.txt`
        for fileName in $fileNumbers; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
            echo $number
            ChangeStructureIfNeeded $OUTPUTDIR_LHC15g2/GammaCalo_$number.root $OUTPUTDIR/GammaCalo_MC_LHC15g2_$number.root $number
            root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_MC_LHC15g2_$number.root\"\,\"$OUTPUTDIR/CutSelection_GammaCalo_MC_LHC15g2_$number.log\"\)
        done;
    fi
    
    if [ $HAVELHC15a3a == 1 ]; then
        ls $OUTPUTDIR_LHC15a3a/GammaCalo_*.root > fileLHC15a3a.txt
        fileNumbers=`cat fileLHC15a3a.txt`
        for fileName in $fileNumbers; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
            echo $number
            ChangeStructureIfNeeded $OUTPUTDIR_LHC15a3a/GammaCalo_$number.root $OUTPUTDIR/GammaCalo_MC_LHC15a3a_$number.root $number
            root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_MC_LHC15a3a_$number.root\"\,\"$OUTPUTDIR/CutSelection_GammaCalo_MC_LHC15a3a_$number.log\"\)
        done;
    fi
    
    if [ $HAVELHC15a3aplus == 1 ]; then
        ls $OUTPUTDIR_LHC15a3aplus/GammaCalo_*.root > fileLHC15a3aplus.txt
        fileNumbers=`cat fileLHC15a3aplus.txt`
        for fileName in $fileNumbers; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
            echo $number
            ChangeStructureIfNeeded $OUTPUTDIR_LHC15a3aplus/GammaCalo_$number.root $OUTPUTDIR/GammaCalo_MC_LHC15a3aplus_$number.root $number
            root -b -l -q -x TaskV1/MakeCutLogCalo.C\(\"$OUTPUTDIR/GammaCalo_MC_LHC15a3aplus_$number.root\"\,\"$OUTPUTDIR/CutSelection_GammaCalo_MC_LHC15a3aplus_$number.log\"\)
        done;
    fi
    
    if [ $MERGEONBINSSingle = 1 ]; then
        binNumbersJJ=`cat binNumbersJJToMerge.txt`
        echo $binNumbersJJ
        ls $OUTPUTDIR_LHC15a3a/GammaCalo_*.root > filetemp.txt
        mkdir -p $OUTPUTDIR/LHC15a3aXFineBins
        for binNumber in $binNumbersJJ; do
            echo $binNumber
            fileNumbers=`cat filetemp.txt`
            for fileName in $fileNumbers; do
                echo $fileName
                number=`echo $fileName  | cut -d "/" -f $NSlashes | cut -d "_" -f 2 | cut -d "." -f1`
                echo $number
                if [ $HAVELHC15a3a == 1 ]; then
                    hadd -f $OUTPUTDIR_LHC15a3a/$binNumber/GammaCalo_$number.root $OUTPUTDIR_LHC15a3a/$binNumber/*/GammaCalo_$number.root
                    ChangeStructureIfNeeded $OUTPUTDIR_LHC15a3a/$binNumber/GammaCalo_$number.root $OUTPUTDIR/LHC15a3aXFineBins/GammaCalo_MC_LHC15a3a$binNumber\_$number.root $number
                fi
                if [ $HAVELHC15a3aplus == 1 ]; then
                    hadd -f $OUTPUTDIR_LHC15a3aplus/$binNumber/GammaCalo_$number.root $OUTPUTDIR_LHC15a3aplus/$binNumber/*/GammaCalo_$number.root
                    ChangeStructureIfNeeded $OUTPUTDIR_LHC15a3aplus/$binNumber/GammaCalo_$number.root $OUTPUTDIR/LHC15a3aXFineBins/GammaCalo_MC_LHC15a3aplus$binNumber\_$number.root $number
                fi
            done;
        done;
    fi

        
    rm $OUTPUTDIR/GammaCalo_MC_LHC15a3a_LHC15a3aplus_*.root
    rm $OUTPUTDIR/GammaCalo_MC_LHC15a3aFinerPtHardBins_LHC15a3aplusFinerPtHardBins_*.root
    
    ls $OUTPUTDIR/GammaCalo_MC_LHC15a3a_*.root > filesForMerging.txt
    filesForMerging=`cat filesForMerging.txt`
    
    if [ $MERGEON == 1 ]; then    
        for fileName in $filesForMerging; do
            echo $fileName
            number=`echo $fileName  | cut -d "/" -f $NSlashes2 | cut -d "_" -f 4 | cut -d "." -f1`
            echo $number
            if [ -f $OUTPUTDIR/GammaCalo_MC_LHC15a3a_$number.root ] && [ -f $OUTPUTDIR/GammaCalo_MC_LHC15a3aplus_$number.root ] ; then
                hadd -f $OUTPUTDIR/GammaCalo_MC_LHC15a3a_LHC15a3aplus_$number.root $OUTPUTDIR/GammaCalo_MC_LHC15a3a_$number.root $OUTPUTDIR/GammaCalo_MC_LHC15a3aplus_$number.root
            fi
        done
    fi
    
    if [ $MERGEONBINS == 1 ]; then    
        filesForMerging=`cat filesForMerging.txt`
        for fileName in $filesForMerging; do
            binsForMerging=`cat binNumbersJJToMerge.txt`
            number=`echo $fileName  | cut -d "/" -f $NSlashes2 | cut -d "_" -f 4 | cut -d "." -f1`
            TOMERGE="";
            for bin in $binsForMerging; do
                echo $OUTPUTDIR/LHC15a3aXFineBins/GammaCalo_MC_LHC15a3a$bin\_$number.root
                if [ -f $OUTPUTDIR/LHC15a3aXFineBins/GammaCalo_MC_LHC15a3a$bin\_$number.root ]; then
                    TOMERGE="$TOMERGE $OUTPUTDIR/LHC15a3aXFineBins/GammaCalo_MC_LHC15a3a$bin"
                    TOMERGE+="_$number.root"
                else 
                    echo "I couldn't find the file for bin $bin, number $number, $OUTPUTDIR/LHC15a3aXFineBins/GammaCalo_MC_LHC15a3a$bin\_$number.root";
                fi
            done;
            hadd -f $OUTPUTDIR/GammaCalo_MC_LHC15a3aFinerPtHardBins_$number.root $TOMERGE

            TOMERGE="";		
            for bin in $binsForMerging; do
                if [ -f $OUTPUTDIR/LHC15a3aXFineBins/GammaCalo_MC_LHC15a3aplus$bin\_$number.root ]; then
                    TOMERGE="$TOMERGE $OUTPUTDIR/LHC15a3aXFineBins/GammaCalo_MC_LHC15a3aplus$bin"
                    TOMERGE+="_$number.root"
                else 
                    echo "I couldn't find the file for bin $bin, number $number";
                fi
            done;
            hadd -f $OUTPUTDIR/GammaCalo_MC_LHC15a3aplusFinerPtHardBins_$number.root $TOMERGE

            hadd -f $OUTPUTDIR/GammaCalo_MC_LHC15a3aFinerPtHardBins_LHC15a3aplusFinerPtHardBins_$number.root $OUTPUTDIR/GammaCalo_MC_LHC15a3aplusFinerPtHardBins_$number.root $OUTPUTDIR/GammaCalo_MC_LHC15a3aFinerPtHardBins_$number.root
        done;
    fi
fi
