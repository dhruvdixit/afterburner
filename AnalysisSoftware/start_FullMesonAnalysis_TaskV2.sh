#! /bin/bash
#
#
#
# This script gests as input a directory where the GammaConvV1 root file is stored,    
# it also needs the desired output directory where the produced root files are put.
# If nothing is given it will use ./ for the input directory and ./Output for the output
#
#Input 1: Root file to analyze Default: AnalyisResults
#Input 2: Input directory  Default:$PWD 
#Input 3: Output directory Default: $PWD/Results  (directory will be created if it does not exist)
#

PROGNAME=$0
AdvMesonQA=""
NEWGammaMacros=1

ONLYCORRECTION=0
ONLYRESULTS=0
HIRUN=0
ONLYCUTS=0
Suffix=eps
MERGINGMC=0
PARTLY=0
DATAFILE=1
MCFILE=1
addedSig=0

AddPileUpCorr=kFALSE
NAMECUTSTUDIES="none"
DoGamma=1
DoPi0=1
DoEta=1
DoPi0InEtaBinning=1
PERIOD=""
NORMALCUTS=0
GSIdata=0
useTHnSparse=1

function GiveBinning13TeV()
{
    echo "How many p_T bins do you want to use for the Pi0?";
    read BinsPtPi0
    correctPi0=1
    echo "You have chosen $BinsPtPi0 bins";

    echo "How many p_T bins do you want to use for the eta meson?";
    read BinsPtEta
    correctEta=1
    echo "You have chosen $BinsPtEta bins";
}

function GiveBinningDalitz7TeV()
{
    echo "How many p_T bins do you want to use for the Pi0? 17(5GeV), 18(7GeV), 19(10GeV), 20(16GeV) 21(20GeV) 22(25GeV) 24 (extra)";
    read answer
    if [ $answer = 17 ]; then
        echo "17 Bins --> Max p_T = 5 GeV ...";
        correctPi0=1
        BinsPtPi0=17
    elif [ $answer = 18 ]; then
        echo "18 Bins --> Max p_T = 7 GeV ...";
        correctPi0=1
        BinsPtPi0=18
    elif [ $answer = 19 ]; then
        echo "19 Bins --> Max p_T = 10 GeV ...";
        correctPi0=1
        BinsPtPi0=19
    elif [ $answer = 20 ]; then
        echo "20 Bins --> Max p_T = 16 GeV ...";
        correctPi0=1
        BinsPtPi0=20
    elif [ $answer = 21 ]; then
        echo "21 Bins --> Max p_T = 20 GeV ...";
        correctPi0=1
        BinsPtPi0=21
    elif [ $answer = 22 ]; then
        echo "22 Bins --> Max p_T = 25 GeV ...";
        correctPi0=1
        BinsPtPi0=22
    elif [ $answer = 24 ]; then
        echo "24 Bins --> Max p_T = 10 GeV ...";
        correctPi0=1
        BinsPtPi0=24
    else
        echo "Pi0 Binning was not set correctly. Please try again.";
        correctPi0=0
    fi
    
    echo "How many p_t bins do you want to use for the eta meson? 8 (4.5 GeV), 9 (6 GeV)"
    read answer
    if [ $answer = 8 ]; then
        echo "8 Bins --> Max p_T = 4.5 GeV ...";
        correctEta=1
        BinsPtEta=8
    elif [ $answer = 9 ]; then
        echo "9 Bins --> Max p_T = 6 GeV ...";
        correctEta=1
        BinsPtEta=9
    else
        echo "Eta Binning was not set correctly. Please try again.";
        correctEta=0
    fi
}

function GiveBinningDirectPhotonHI()
{
    DoEta=0;
    DoPi0InEtaBinning=0;

    echo "How many p_T bins do you want to use for the Pi0? 17(8GeV), 18(11GeV) 19 (14GeV)";
    read answer
    if [ $answer = 17 ]; then
        echo "17 Bins --> Max p_T = 8 GeV ...";
        correctPi0=1
        BinsPtPi0=17
    elif [ $answer = 18 ]; then
        echo "18 Bins --> Max p_T = 11 GeV ...";
        correctPi0=1
        BinsPtPi0=18
    elif [ $answer = 19 ]; then
        echo "19 Bins --> Max p_T = 20 GeV ...";
        correctPi0=1
        BinsPtPi0=18
    else
        echo "Pi0 Binning was not set correctly. Please try again.";
        correctPi0=0
    fi
}

function GiveBinningDirectPhotonpPb()
{    
    echo "How many p_T bins do you want to use for the Pi0? 17(8GeV), 18(11GeV) 19 (14GeV)";
    read answer
    if [ $answer = 17 ]; then
        echo "17 Bins --> Max p_T = 8 GeV ...";
        correctPi0=1
        BinsPtPi0=17
    elif [ $answer = 18 ]; then
        echo "18 Bins --> Max p_T = 11 GeV ...";
        correctPi0=1
        BinsPtPi0=18
    elif [ $answer = 19 ]; then
        echo "19 Bins --> Max p_T = 20 GeV ...";
        correctPi0=1
        BinsPtPi0=18
    else
        echo "Pi0 Binning was not set correctly. Please try again.";
        correctPi0=0
    fi
}

function GiveBinningDirectPhoton2760TeV()
{
    DoEta=0;
    DoPi0InEtaBinning=0;

    echo "How many p_T bins do you want to use for the Pi0? 13(5.5GeV), 14(7GeV) 15 (10GeV)";
    read answer
    if [ $answer = 13 ]; then
        echo "13 Bins --> Max p_T = 5.5 GeV ...";
        correctPi0=1
        BinsPtPi0=13
    elif [ $answer = 14 ]; then
        echo "14 Bins --> Max p_T = 7 GeV ...";
        correctPi0=1
        BinsPtPi0=14
    elif [ $answer = 15 ]; then
        echo "15 Bins --> Max p_T = 10 GeV ...";
        correctPi0=1
        BinsPtPi0=15
    else
        echo "Pi0 Binning was not set correctly. Please try again.";
        correctPi0=0
    fi
}

function GiveBinningDirectPhoton7TeV()
{
    DoPi0InEtaBinning=0;
    DoEta=0;

    echo "How many p_T bins do you want to use for the Pi0? 19(10GeV), 20(12GeV), 21(16GeV), 22(20GeV) 23 (25GeV)";
    read answer
    if [ $answer = 19 ]; then
        echo "19 Bins --> Max p_T = 8 GeV ...";
        correctPi0=1
        BinsPtPi0=19
    elif [ $answer = 20 ]; then
        echo "20 Bins --> Max p_T = 12 GeV ...";
        correctPi0=1
        BinsPtPi0=20
    elif [ $answer = 21 ]; then
        echo "21 Bins --> Max p_T = 16 GeV ...";
        correctPi0=1
        BinsPtPi0=21
    elif [ $answer = 22 ]; then
        echo "22 Bins --> Max p_T = 20 GeV ...";
        correctPi0=1
        BinsPtPi0=22
    elif [ $answer = 23 ]; then
        echo "23 Bins --> Max p_T = 25 GeV ...";
        correctPi0=1
        BinsPtPi0=23
    else
        echo "Pi0 Binning was not set correctly. Please try again.";
        correctPi0=0
    fi
}

function GiveBinning7TeV()
{
    echo "how many p_t bins do you want to use for the pi0? 22(7gev), 27(8gev), 28(10gev), 29(12gev) 30 (16gev) 32 (25gev)";
    
    read answer
    if [ $answer = 26 ]; then
        echo "26 bins --> max p_t = 7 gev ...";
        correctpi0=1
        BinsPtPi0=26
    elif [ $answer = 27 ]; then
        echo "27 bins --> max p_t = 8 gev ...";
        correctpi0=1
        BinsPtPi0=27
    elif [ $answer = 28 ]; then
        echo "28 bins --> max p_t = 10 gev ...";
        correctpi0=1
        BinsPtPi0=28
    elif [ $answer = 29 ]; then
        echo "29 bins --> max p_t = 12 gev ...";
        correctpi0=1
        BinsPtPi0=29
    elif [ $answer = 30 ]; then
        echo "30 bins --> max p_t = 16 gev ...";
        correctpi0=1
        BinsPtPi0=30
    elif [ $answer = 32 ]; then
        echo "32 bins --> max p_t = 25 gev ...";
        correctpi0=1
        BinsPtPi0=32
    else
        echo "pi0 binning was not set correctly. please try again.";
        correctpi0=0
    fi
    
    echo "how many p_t bins do you want to use for the eta? 10(4gev), 11(6gev), 12(8gev)";
    read answer
    if [ $answer = 10 ]; then
        echo "10 bins --> max p_t = 4 gev ...";
        correcteta=1
        BinsPtEta=10
    elif [ $answer = 11 ]; then
        echo "11 bins --> max p_t = 6 gev ...";
        correcteta=1
        BinsPtEta=11
    elif [ $answer = 12 ]; then
        echo "12 bins --> max p_t = 8 gev ...";
        correcteta=1
        BinsPtEta=12
    else
        echo "eta binning was not set correctly. please try again.";
        correcteta=0
    fi
    BinsPtPi0pileup=19
    BinsPtEtapileup=7
}

function GiveBinning8TeV()
{
    echo "How many p_T bins do you want to use for the Pi0? 26(7GeV), 27(8GeV), 28(10GeV), 29(12GeV) 30 (16GeV) 33 (25GeV)";
    
    read answer
    if [ $answer = 26 ]; then
        echo "26 Bins --> Max p_T = 7 GeV ...";
        correctPi0=1
        BinsPtPi0=26
    elif [ $answer = 27 ]; then
        echo "27 Bins --> Max p_T = 8 GeV ...";
        correctPi0=1
        BinsPtPi0=27
    elif [ $answer = 28 ]; then
        echo "28 Bins --> Max p_T = 10 GeV ...";
        correctPi0=1
        BinsPtPi0=28
    elif [ $answer = 29 ]; then
        echo "29 Bins --> Max p_T = 12 GeV ...";
        correctPi0=1
        BinsPtPi0=29
    elif [ $answer = 30 ]; then
        echo "30 Bins --> Max p_T = 16 GeV ...";
        correctPi0=1
        BinsPtPi0=30
    elif [ $answer = 33 ]; then
        echo "33 Bins --> Max p_T = 25 GeV ...";
        correctPi0=1
        BinsPtPi0=33
    else
        echo "Pi0 Binning was not set correctly. Please try again.";
        correctPi0=0
    fi
    
    echo "How many p_T bins do you want to use for the Eta? 10(4GeV), 12(6GeV), 13(8GeV)";
    read answer
    if [ $answer = 10 ]; then
        echo "10 Bins --> Max p_T = 4 GeV ...";
        correctEta=1
        BinsPtEta=10
    elif [ $answer = 12 ]; then
        echo "12 Bins --> Max p_T = 6 GeV ...";
        correctEta=1
        BinsPtEta=12
    elif [ $answer = 13 ]; then
        echo "13 Bins --> Max p_T = 8 GeV ...";
        correctEta=1
        BinsPtEta=13
    elif [ $answer = 14 ]; then
        echo "14 Bins --> Max p_T = 10 GeV ...";
        correctEta=1
        BinsPtEta=14
    else
        echo "Eta Binning was not set correctly. Please try again.";
        correctEta=0
    fi
}

function GiveBinning900GeV()
{
    echo "How many p_T bins do you want to use? 10(3GeV), 11(4GeV)";
    read answer
    if [ $answer = 10 ]; then
        echo "10 Bins --> Max p_T = 3 GeV ...";
        correctPi0=1
        BinsPtPi0=10
    elif [ $answer = 11 ]; then
        echo "11 Bins --> Max p_T = 4 GeV ...";
        correctPi0=1
        BinsPtPi0=11
    else
        echo "Pi0 Binniing was not set correctly. Please try again.";
    fi
    
    echo "How many p_t bins do you want to use for the eta meson? 2 (1.8 GeV), 3 (4 GeV)"
    read answer
    if [ $answer = 2 ]; then
        echo "2 Bins --> Max p_T = 1.8 GeV ...";
        correctEta=1
        BinsPtEta=2
    elif [ $answer = 3 ]; then
        echo "3 Bins --> Max p_T = 4 GeV ...";
        correctEta=1
        BinsPtEta=3
    else
        echo "Eta Binning was not set correctly. Please try again.";
        correctEta=0
    fi
}

function GiveBinningDirectPhoton900GeV()
{
    DoEta=0;
    DoPi0InEtaBinning=0;

    echo "How many p_T bins do you want to use? 10(3GeV), 11(4GeV)";
    read answer
    if [ $answer = 7 ]; then
        echo "7 Bins --> Max p_T = 3 GeV ...";
        correctPi0=1
        BinsPtPi0=7
    elif [ $answer = 11 ]; then
        echo "12 Bins --> Max p_T = 4 GeV ...";
        correctPi0=1
        BinsPtPi0=11
    elif [ $answer = 12 ]; then
        echo "13 Bins --> Max p_T = 6 GeV ...";
        correctPi0=1
        BinsPtPi0=12
    else
        echo "Pi0 Binning was not set correctly. Please try again.";
    fi
}

function GiveBinning2760GeV()
{
    echo "How many p_T bins do you want to use? 17 (6GeV), 18 (8GeV), 19 (10GeV), for conv calo: 20 (12 GeV), 21 (15 GeV), 22 (20 GeV), 23 (25 GeV), 24 (30 GeV), ";
    echo "only for trigger or Calo: 21 (10GeV),  24 (14GeV), 25 (16GeV), 26 (20 GeV), 27 (24 GeV), 28 (28GeV) 29 (30GeV)";
    read answer
    if [ $answer = 17 ]; then
        echo "17 Bins --> Max p_T = 6 GeV ...";
        correctPi0=1
        BinsPtPi0=17
    elif [ $answer = 18 ]; then
        echo "18 Bins --> Max p_T = 8 GeV ..., if trigg 7 GeV ...";
        correctPi0=1
        BinsPtPi0=18
    elif [ $answer = 19 ]; then
        echo "19 Bins --> Max p_T = 10 GeV ..., if trigg 8 GeV ...";
        correctPi0=1
        BinsPtPi0=19
    elif [ $answer = 20 ]; then
        echo "20 Bins --> Max p_T = 12 GeV ..., if trigg 9 GeV ...";
        correctPi0=1
        BinsPtPi0=20
    elif [ $answer = 21 ]; then
        echo "21 Bins --> Max p_T = 15 GeV ..., if trigg 10 GeV ...";
        correctPi0=1
        BinsPtPi0=21
    elif [ $answer = 22 ]; then
        echo "22 Bins --> Max p_T = 20 GeV ..., if trigg 11 GeV ...";
        correctPi0=1
        BinsPtPi0=22
    elif [ $answer = 23 ]; then
        echo "23 Bins --> Max p_T = 25 GeV ..., if trigg 12 GeV ...";
        correctPi0=1
        BinsPtPi0=23
    elif [ $answer = 24 ]; then
        echo "24 Bins --> Max p_T = 30 GeV ..., if trigg 14 GeV ...";
        correctPi0=1
        BinsPtPi0=24
    elif [ $answer = 25 ]; then
        echo "25 Bins --> Max p_T = 16 GeV ...";
        correctPi0=1
        BinsPtPi0=25
    elif [ $answer = 26 ]; then
        echo "25 Bins --> Max p_T = 20 GeV ...";
        correctPi0=1
        BinsPtPi0=26
    elif [ $answer = 27 ]; then
        echo "24 Bins --> Max p_T = 24 GeV ...";
        correctPi0=1
        BinsPtPi0=27
    elif [ $answer = 28 ]; then
        echo "28 Bins --> Max p_T = 28 GeV ...";
        correctPi0=1
        BinsPtPi0=28
    elif [ $answer = 29 ]; then
        echo "29 Bins --> Max p_T = 30 GeV ...";
        correctPi0=1
        BinsPtPi0=29
    else
        echo "Pi0 Binning was not set correctly. Please try again.";
    fi
    
    if [ $DoEta -eq 1 ] || [ $DoPi0InEtaBinning -eq 1 ]; then
        echo "How many p_t bins do you want to use for the eta meson? 6 (4. GeV), 7 (6 GeV), for conv calo: 8 (8 GeV), 9 (10 GeV), 10 (12 GeV), 11 (16 GeV), 12 (20 GeV), 13 (25 GeV)"
        read answer
        if [ $answer = 6 ]; then
            echo "6 Bins --> Max p_T = 4. GeV ...";
            correctEta=1
            BinsPtEta=6
        elif [ $answer = 7 ]; then
            echo "7 Bins --> Max p_T = 6 GeV ...";
            correctEta=1
            BinsPtEta=7
        elif [ $answer = 8 ]; then
            echo "8 Bins --> Max p_T = 8 GeV ...";
            correctEta=1
            BinsPtEta=8
        elif [ $answer = 9 ]; then
            echo "9 Bins --> Max p_T = 10 GeV ...";
            correctEta=1
            BinsPtEta=9
        elif [ $answer = 10 ]; then
            echo "10 Bins --> Max p_T = 12 GeV ...";
            correctEta=1
            BinsPtEta=10
        elif [ $answer = 11 ]; then
            echo "11 Bins --> Max p_T = 16 GeV ...";
            correctEta=1
            BinsPtEta=11
        elif [ $answer = 12 ]; then
            echo "12 Bins --> Max p_T = 20 GeV ...";
            correctEta=1
            BinsPtEta=12
        elif [ $answer = 13 ]; then
            echo "13 Bins --> Max p_T = 25 GeV ...";
            correctEta=1
            BinsPtEta=13

        else
            echo "Eta Binning was not set correctly. Please try again.";
            correctEta=0
        fi
    else 
        correctEta=1
    fi    
}

function GiveBinning2760GeVMerged()
{
    echo "How many p_T bins do you want to use for merged analysis? 25 (16 GeV), 26 (18 GeV), 27 (22 GeV), 28 (26 GeV), 29 (30 GeV), 30 (35 GeV), 31 (40 GeV), 32 (50 GeV)";
    read answer
    if [ $answer = 25 ]; then
        echo "25 Bins --> Max p_T = 16 GeV ...";
        correctPi0=1
        BinsPtPi0=25
    elif [ $answer = 26 ]; then
        echo "25 Bins --> Max p_T = 18 GeV ...";
        correctPi0=1
        BinsPtPi0=26
    elif [ $answer = 27 ]; then
        echo "24 Bins --> Max p_T = 22 GeV ...";
        correctPi0=1
        BinsPtPi0=27
    elif [ $answer = 28 ]; then
        echo "28 Bins --> Max p_T = 26 GeV ...";
        correctPi0=1
        BinsPtPi0=28
    elif [ $answer = 29 ]; then
        echo "29 Bins --> Max p_T = 30 GeV ...";
        correctPi0=1
        BinsPtPi0=29
    elif [ $answer = 30 ]; then
        echo "30 Bins --> Max p_T = 35 GeV ...";
        correctPi0=1
        BinsPtPi0=30
    elif [ $answer = 31 ]; then
        echo "30 Bins --> Max p_T = 40 GeV ...";
        correctPi0=1
        BinsPtPi0=30
    elif [ $answer = 32 ]; then
        echo "32 Bins --> Max p_T = 50 GeV ...";
        correctPi0=1
        BinsPtPi0=32
        else
        echo "Pi0 Binning was not set correctly. Please try again.";
    fi
    DoEta=0;
    DoPi0InEtaBinning=0;
    correctEta=1;
}


function GiveBinningHI()
{
    if [ $DoPi0 -eq 1 ] ; then
        echo "How many p_T bins do you want to use for Pi0?  19 (10GeV), 20(12GeV), 21(14GeV)";
        read answer
        if [ $answer = 20 ]; then
            echo "20 Bins --> Max p_T = 12 GeV ...";
            correctPi0=1
            BinsPtPi0=20
        elif [ $answer = 21 ]; then
            echo "21 Bins --> Max p_T = 14 GeV ...";
            correctPi0=1
            BinsPtPi0=21
        elif [ $answer = 19 ]; then
            echo "19 Bins --> Max p_T = 10 GeV ...";
            correctPi0=1
            BinsPtPi0=19
        else
            echo "Pi0 Binning was not set correctly. Please try again.";
            correctPi0=0
        fi
    fi
    if [ $DoEta -eq 1 ] || [ $DoPi0InEtaBinning -eq 1 ]; then
        echo "How many p_T bins do you want to use for Eta? 10(6GeV), 11(8GeV), 12(10GeV), 13(10GeV), 8(10GeV), 9(10GeV), 15 (19GeV)";
        read answer
        if [ $answer = 11 ]; then
            echo "11 Bins --> Max p_T = 8 GeV ...";
            correctEta=1
            BinsPtEta=11
        elif [ $answer = 12 ]; then
            echo "12 Bins --> Max p_T = 10 GeV ...";
            correctEta=1
            BinsPtEta=12
        elif [ $answer = 13 ]; then
            echo "13 Bins --> Max p_T = 10 GeV ...";
            correctEta=1
            BinsPtEta=13
        elif [ $answer = 9 ]; then
            echo "9 Bins --> Max p_T = 10 GeV ...";
            correctEta=1
            BinsPtEta=9
        elif [ $answer = 8 ]; then
            echo "8 Bins --> Max p_T = 10 GeV ...";
            correctEta=1
            BinsPtEta=9
        elif [ $answer = 15 ]; then
            echo "15 Bins --> Max p_T = 19 GeV ...";
            correctEta=1
            BinsPtEta=15
        elif [ $answer = 10 ]; then
            echo "10 Bins --> Max p_T = 6 GeV ...";
            correctEta=1
            BinsPtEta=10    
        else
            echo "Pi0 Binning was not set correctly. Please try again.";
            correctEta=0
        fi
    fi
#    DoEta=1
#    DoPi0InEtaBinning=1
}

function GiveBinningpPb()
{
    if [ $DoPi0 -eq 1 ] || [ $DoGamma -eq 1 ]; then
        echo "How many p_T bins do you want to use for Pi0/direct photon?  27 (7 GeV), 28 (8 GeV), 29 (10 GeV), 30 (12 GeV), 31 (14 GeV), for Calo measurements also 32 (16 GeV), 33 (18 GeV), 34 (20 GeV), 35 (22 GeV), 36 (26 GeV), 37 (30 GeV)";
        echo "for calo triggers bins reach to 42."
        read answer
        if [ $answer = 27 ]; then
            echo "27 Bins --> Max p_T = 7 GeV ...";
            correctPi0=1
            BinsPtPi0=27
        elif [ $answer = 28 ]; then
            echo "28 Bins --> Max p_T = 8 GeV ...";
            correctPi0=1
            BinsPtPi0=28
        elif [ $answer = 29 ]; then
            echo "29 Bins --> Max p_T = 10 GeV ...";
            correctPi0=1
            BinsPtPi0=29
        elif [ $answer = 30 ]; then
            echo "30 Bins --> Max p_T = 12 GeV ...";
            correctPi0=1
            BinsPtPi0=30 
        elif [ $answer = 31 ]; then
            echo "31 Bins --> Max p_T = 14 GeV ...";
            correctPi0=1
            BinsPtPi0=31 
        elif [ $answer = 32 ]; then
            echo "32 Bins --> Max p_T = 16 GeV ...";
            correctPi0=1
            BinsPtPi0=32 
        elif [ $answer = 33 ]; then
            echo "33 Bins --> Max p_T = 18 GeV ...";
            correctPi0=1
            BinsPtPi0=33 
        elif [ $answer = 34 ]; then
            echo "34 Bins --> Max p_T = 20 GeV ...";
            correctPi0=1
            BinsPtPi0=34 
        elif [ $answer = 35 ]; then
            echo "35 Bins --> Max p_T = 22 GeV ...";
            correctPi0=1
            BinsPtPi0=35 
        elif [ $answer = 36 ]; then
            echo "36 Bins --> Max p_T = 26 GeV ...";
            correctPi0=1
            BinsPtPi0=36 
        elif [ $answer = 37 ]; then
            echo "37 Bins --> Max p_T = 30 GeV ...";
            correctPi0=1
            BinsPtPi0=37 
        elif [ $answer = 38 ]; then
            echo "38 Bins";
            correctPi0=1
            BinsPtPi0=38 
        elif [ $answer = 39 ]; then
            echo "39 Bins";
            correctPi0=1
            BinsPtPi0=39 
        elif [ $answer = 40 ]; then
            echo "40 Bins";
            correctPi0=1
            BinsPtPi0=40 
        elif [ $answer = 41 ]; then
            echo "41 Bins";
            correctPi0=1
            BinsPtPi0=41 
        elif [ $answer = 42 ]; then
            echo "42 Bins";
            correctPi0=1
            BinsPtPi0=42 
        else
            echo "Pi0 Binning was not set correctly. Please try again.";
            correctPi0=0
        fi
    else
        correctPi0=1
    fi    
    if [ $DoEta -eq 1 ] || [ $DoPi0InEtaBinning -eq 1 ]; then 
        echo "How many p_t bins do you want to use for the eta meson? 12 (4 GeV), 14 (6 GeV), 15 (8 GeV), 16 (10 GeV), for calorimeters 17 (12 GeV), 18 (14 GeV), 19 (16 GeV), 20 (20 GeV), 21 (25 GeV), 22 (30 GeV)";
        echo "for calo triggers bins reach to 26."
        read answer
        if [ $answer = 12 ]; then
            echo "12 Bins --> Max p_T = 4. GeV ...";
            correctEta=1
            BinsPtEta=12
        elif [ $answer = 14 ]; then
            echo "14 Bins --> Max p_T = 6 GeV ...";
            correctEta=1
            BinsPtEta=14
        elif [ $answer = 15 ]; then
            echo "15 Bins --> Max p_T = 8 GeV ...";
            correctEta=1
            BinsPtEta=15
        elif [ $answer = 16 ]; then
            echo "16 Bins --> Max p_T = 10 GeV ...";
            correctEta=1
            BinsPtEta=16   
        elif [ $answer = 17 ]; then
            echo "17 Bins --> Max p_T = 12 GeV ...";
            correctEta=1
            BinsPtEta=17   
        elif [ $answer = 18 ]; then
            echo "18 Bins --> Max p_T = 14 GeV ...";
            correctEta=1
            BinsPtEta=18   
        elif [ $answer = 19 ]; then
            echo "19 Bins --> Max p_T = 16 GeV ...";
            correctEta=1
            BinsPtEta=19   
        elif [ $answer = 20 ]; then
            echo "20 Bins --> Max p_T = 20 GeV ...";
            correctEta=1
            BinsPtEta=20   
        elif [ $answer = 21 ]; then
            echo "21 Bins --> Max p_T = 25 GeV ...";
            correctEta=1
            BinsPtEta=21   
        elif [ $answer = 22 ]; then
            echo "22 Bins --> Max p_T = 30 GeV ...";
            correctEta=1
            BinsPtEta=22   
        elif [ $answer = 23 ]; then
            echo "23 Bins";
            correctEta=1
            BinsPtEta=23   
        elif [ $answer = 24 ]; then
            echo "24 Bins";
            correctEta=1
            BinsPtEta=24   
        elif [ $answer = 25 ]; then
            echo "25 Bins";
            correctEta=1
            BinsPtEta=25   
        elif [ $answer = 26 ]; then
            echo "26 Bins";
            correctEta=1
            BinsPtEta=26   
#         elif [ $answer = 27 ]; then
#             echo "27 Bins";
#             correctEta=1
#             BinsPtEta=27   
        else
            echo "Eta Binning was not set correctly. Please try again.";
        fi
        correctEta=0
    fi
}


function ExtractSignal()
{
    root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\($1\,$mode\,$useTHnSparse\)  
}

function ExtractSignalGamma()
{
    root -x -l -b -q TaskV1/ExtractGammaSignal.C\+\($1\,$addedSig\,$mode\)
}

function ExtractSignalGammaV2()
{
    root -x -l -b -q TaskV1/ExtractGammaSignalV2.C\+\($1\,$addedSig\,$mode\)
}


function CorrectSignal()
{
    root -x -l -b -q TaskV1/CorrectSignalV2.C\+\(\"$1\"\,\"$2\"\,\"$3\"\,\"$4\"\,\"$5\"\,\"$6\"\,\"$energy\"\,\"\"\,\"$ESTIMATEPILEUP\"\,kFALSE\,$mode\)
}

function CorrectSignalGamma()
{
    root -x -b -q -l CompileCorrectGamma.C\+\+
    root -x -l -b -q TaskV1/CorrectGamma.C\+\(\"$1\"\,\"$2\"\,\"$3\"\,\"$4\"\,\"$5\"\,\"$6\"\,\"$energy\"\,\"\"\,\"$ESTIMATEPILEUP\"\,$mode\)
}

function CorrectSignalGammaV2()
{
    root -x -b -q -l CompileCorrectGammaV2.C\+\+
    root -x -l -b -q TaskV1/CorrectGammaV2.C\+\(\"$1\"\,\"$2\"\,\"$3\"\,\"$4\"\,\"$5\"\,\"$6\"\,\"$energy\"\,\"\"\,\"$ESTIMATEPILEUP\"\,$mode\)
}

function CreateFinalResults() 
{
    if [ $mode != 2 ] && [ $mode != 4 ]; then 
        root -x -l -b -q TaskV1/ProduceFinalResults.C\+\($1,\"\"\,\"kTRUE\"\,$AddPileUpCorr\,$mode\)
    fi    
}

function ProduceFinalResultspPb() 
{
    root -x -l -b -q TaskV1/ProduceFinalResultspPb.C\+\(\"$1\"\,\"$2\"\,\"$3\"\,\"$4\"\,\"$5\"\,\"$6\"\,\"$7\"\,kFALSE\)
    
}

function CreateGammaFinalResults() 
{
    root -x -l -b -q TaskV1/CalculateGammaToPi0V2.C++\(\"$1\"\,\"$2\"\,\"$3\"\,\"$4\"\,\"$5\"\,\"$6\"\,\"$energy\",$mode\)
}

function Usage() 
{
    echo -e "
This Script is provided by the Gamma Conversion Group of ALICE 
the main developers are 
    Friederike Bock \t friederike.bock@cern.ch
    Ana Marin \t\t marin@physi.uni-heidelberg.de  
            
If there are any complications with running this script do not hesitate to connect them.


How to use this script? 
$PROGNAME -h  \t\t\t\t\t usage will be displayed 
$PROGNAME --help \t\t\t\t usage will be displayed 
$PROGNAME -c data.root suffix \t\t\t Will only correct and produce the final results for already existing RAWdata \n \t\t\t\t\t\t\t\t\t and produce the graphical output in the specified suffix-format.\n
$PROGNAME -d data.root suffix \t\t\t Will only fullfil cutstudies and produce the final results for already existing RAWdata \n \t\t\t\t\t\t\t\t\t and produce the graphical output in the specified suffix-format.\n
$PROGNAME -m DirectoryOfMergedOutputs suffix \t Automatic merging for LHC10bc and LHC10de for efficiencies will be done \n \t\t\t\t\t\t\t\t\t according to the fraction in Data, be careful files have to be arranged in a certain structure \n
    \t\t\t\t\t\t\t\t DataRootFile=DirectoryOfMergedOutputs/mergedALL/GammaConvV1Data.root
    \t\t\t\t\t\t\t\t MCRootFile=DirectoryOfMergedOutputs/mergedALL/GammaConvV1MC.root
    \t\t\t\t\t\t\t\t MCRootFileBC=DirectoryOfMergedOutputs/mergedBC/GammaConvV1MC.root
    \t\t\t\t\t\t\t\t MCRootFileD=DirectoryOfMergedOutputs/mergedDE/GammaConvV1MC.root\n 
$PROGNAME -r data.root suffix \t\t\t Will only execute the production of the final results and \n \t\t\t\t\t\t\t\t\t produce the graphical output in the specified suffix-format.\n
$PROGNAME data.root MC.root suffix \t \t Will execute Gamma Conversion Analysis for data.root file and MC.root file \n \t\t\t\t\t\t\t\t\t and produce the graphical output in the specified suffix-format.\n
$PROGNAME  *-*gammaOff* \t\t\t gamma calculation switched off \n
$PROGNAME  *-*gammaOnly* \t\t\t gamma calculation only\n
$PROGNAME  *-*pi0Only* \t\t\t\t pi0 calculation only\n
$PROGNAME  *-*pi0etaOnly* \t\t\t pi0 in eta binnin calculation only\n
$PROGNAME  *-*etaOnly* \t\t\t\t eta calculation only\n
$PROGNAME  *-*etaOff* \t\t\t\t eta calculation switched off\n

This script needs as a basis the output from the GammaConversion-Software which is provided with the Aliroot software, both the 'data.root' and the 'MC.root' have to be output files of this. The script then will check which cutnumbers are in these files and will ask you which exactly you want to analyse, furthermore you have to set a standard cut which has to be always the first in the CutLogFile. Because for this cut the systematic errors will be calculated. Not only one analysis will be fullfiled, you can additionally choose to do a Alpha studie or Chi2 of the meson as well which will give you the oportunity to calculate two indepent error due to cut variation. Additionally the CorrectSignal.C will correct the spectrum for all possible contributions and afterwards calculate the systematic error due to yield extraction. All these error will then enter the final results where you will have plots with only statistical errors as well as systematic + static errors. Several data output files are created, and 
stored in the corresponding cut-directory or the working directory for the cutsstudies file. 

    "
    exit 
}

if [ "$#" == "0" ]; then
    echo -e "
$PROGNAME -h  \t\t\t\t\t usage will be displayed 
$PROGNAME --help \t\t\t\t usage will be displayed 
$PROGNAME -c data.root suffix \t\t\t Will only correct and produce the final results for already existing RAWdata \n \t\t\t\t\t\t\t\t\t and produce the graphical output in the specified suffix-format.\n
$PROGNAME -d data.root suffix \t\t\t Will only fullfil cutstudies and produce the final results for already existing RAWdata \n \t\t\t\t\t\t\t\t\t and produce the graphical output in the specified suffix-format.\n
$PROGNAME -m DirectoryOfMergedOutputs suffix \t Automatic merging for LHC10bc and LHC10de for efficiencies will be done \n \t\t\t\t\t\t\t\t\t according to the fraction in Data, be careful files have to be arranged in a certain structure \n
    \t\t\t\t\t\t\t\t DataRootFile=DirectoryOfMergedOutputs/mergedALL/GammaConvV1Data.root
    \t\t\t\t\t\t\t\t MCRootFile=DirectoryOfMergedOutputs/mergedALL/GammaConvV1MC.root
    \t\t\t\t\t\t\t\t MCRootFileBC=DirectoryOfMergedOutputs/mergedBC/GammaConvV1MC.root
    \t\t\t\t\t\t\t\t MCRootFileD=DirectoryOfMergedOutputs/mergedDE/GammaConvV1MC.root\n 
$PROGNAME -r data.root suffix \t\t\t Will only execute the production of the final results and \n \t\t\t\t\t\t\t\t\t produce the graphical output in the specified suffix-format.\n
$PROGNAME data.root MC.root suffix \t \t Will execute Gamma Conversion Analysis for data.root file and MC.root file \n \t\t\t\t\t\t\t\t\t and produce the graphical output in the specified suffix-format.\n
$PROGNAME  *-*gammaOff* \t\t\t gamma calculation switched off \n
$PROGNAME  *-*gammaOnly* \t\t\t gamma calculation only\n
$PROGNAME  *-*pi0Only* \t\t\t\t pi0 calculation only\n
$PROGNAME  *-*pi0etaOnly* \t\t\t pi0 in eta binnin calculation only\n
$PROGNAME  *-*etaOnly* \t\t\t\t eta calculation only\n
$PROGNAME  *-*etaOff* \t\t\t\t eta calculation switched off\n
"
    exit
fi

echo $1
echo $2
echo $3
echo $4


if [[ "$1" == *-*gammaOff* ]]; then
    DoGamma=0
    echo "gamma calculation switched off"
fi
etaOnly=0


if [[ "$1" == *-*etaOff* ]]; then
    DoPi0=1
    DoEta=0
    DoPi0InEtaBinning=0
    echo "eta calculation switched off"
fi

if [[ "$1" == *-*etaOnly* ]]; then
    DoPi0=0
    DoEta=1
    DoPi0InEtaBinning=0
    echo "eta calculation only"
fi

if [[ "$1" == *-*pi0etaOnly* ]]; then
    DoPi0=0
    DoEta=0
    DoPi0InEtaBinning=1
    echo "pi0 in eta binning calculation only"
fi

if [[ "$1" == *-*pi0Only* ]]; then
    DoPi0=1
    DoEta=0
    DoPi0InEtaBinning=0
    echo "pi0 calculation only"
fi

if [[ "$1" == *-*gammaOnly* ]]; then
    DoPi0=0
    DoEta=0
    DoPi0InEtaBinning=0
    DoGamma=1
    echo "gamma calculation only"
fi

if [[ "$1" == *-*aPUC* ]]; then
    AddPileUpCorr=kTRUE
    echo "additionally pileup correction on"
fi

if [[ "$1" == *-h* ]] ; then
    Usage
elif [[ "$1" == *-mAddSig2760GeVWOSDDA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConv_Data-WOSDD_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConv_MC-WOSDD_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConv_MC-WOSDD_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConv_MC-WOSDD_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mJJMCCC11aMB* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    CONFIG=$3
    Suffix=$4
    useTHnSparse=0
    minPtMergePi0=3
    minPtMergeEta=0
    DataRootFile=$DIRECTORY/GammaConvCalo_LHC11a-pass4_$CONFIG.root
    MCRootFile=$DIRECTORY/GammaConvCalo_MC_LHC12f1a_LHC12f1b_LHC12i3_$CONFIG.root
    MCRootFileAddSig=$DIRECTORY/GammaConvCalo_MC_LHC15g1aFinerPtHardBins_$CONFIG.root
    addedSig=2
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#   exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mJJMCCC13gINT7* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    CONFIG=$3
    Suffix=$4
    useTHnSparse=0
    minPtMergePi0=3
    minPtMergeEta=0
    DataRootFile=$DIRECTORY/GammaConvCalo_LHC13g-pass3_$CONFIG.root
    MCRootFile=$DIRECTORY/GammaConvCalo_MC_LHC15g2_$CONFIG.root
    MCRootFileAddSig=$DIRECTORY/GammaConvCalo_MC_LHC15a3aFinerPtHardBins_LHC15a3aplusFinerPtHardBins_$CONFIG.root
    addedSig=2
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#   exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mJJMCCC11aEMC1* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    CONFIG=$3
    Suffix=$4
    useTHnSparse=0
    minPtMergePi0=3
    minPtMergeEta=0
    DataRootFile=$DIRECTORY/GammaConvCalo_LHC11a-pass4_$CONFIG.root
    MCRootFile=$DIRECTORY/GammaConvCalo_MC_LHC12f1a_LHC12f1b_$CONFIG.root
    MCRootFileAddSig=$DIRECTORY/GammaConvCalo_MC_LHC15g1aFinerPtHardBins_$CONFIG.root
    addedSig=2
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#   exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mJJMCEMC11aMB* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    CONFIG=$3
    Suffix=$4
    useTHnSparse=0
    minPtMergePi0=5
    minPtMergeEta=4
    DataRootFile=$DIRECTORY/GammaCalo_LHC11a-pass4_$CONFIG.root
    MCRootFile=$DIRECTORY/GammaCalo_MC_LHC12f1a_LHC12f1b_$CONFIG.root
    MCRootFileAddSig=$DIRECTORY/GammaCalo_MC_LHC15g1aFinerPtHardBins_$CONFIG.root
    addedSig=2
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
        echo "The MC file specified is $MCRootFileAddSig"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mJJMCEMC13gINT7* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    CONFIG=$3
    Suffix=$4
    useTHnSparse=0
    minPtMergePi0=5
    minPtMergeEta=4
    DataRootFile=$DIRECTORY/GammaCalo_LHC13g-pass1_$CONFIG.root
    MCRootFile=$DIRECTORY/GammaCalo_MC_LHC15g2_$CONFIG.root
    MCRootFileAddSig=$DIRECTORY/GammaCalo_MC_LHC15a3aFinerPtHardBins_LHC15a3aplusFinerPtHardBins_$CONFIG.root
    addedSig=2
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#   exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
        echo "The MC file specified is $MCRootFileAddSig"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mMerged11a* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    CONFIG=$3
    Suffix=$4
    useTHnSparse=0
    minPtMergePi0=7
    minPtMergeEta=20
    DataRootFile=$DIRECTORY/GammaCaloMerged_LHC11a-pass4_$CONFIG.root
    MCRootFile=$DIRECTORY/GammaCaloMerged_MC_LHC15g1aFinerPtHardBins_$CONFIG.root
    MCRootFileGJ=$DIRECTORY/GammaCaloMerged_MC_LHC15g1b_$CONFIG.root
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#   exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
        echo "The MC file specified is $MCRootFileGJ"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mMerged13g* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    CONFIG=$3
    Suffix=$4
    useTHnSparse=0
    minPtMergePi0=7
    minPtMergeEta=20
    DataRootFile=$DIRECTORY/GammaCaloMerged_LHC13g-pass1_$CONFIG.root
    MCRootFile=$DIRECTORY/GammaCaloMerged_MC_LHC15a3aFinerPtHardBins_LHC15a3aplusFinerPtHardBins_$CONFIG.root
    MCRootFileGJ=$DIRECTORY/GammaCaloMerged_MC_LHC15a3b_$CONFIG.root
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#   exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
        echo "The MC file specified is $MCRootFileGJ"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi

    
elif [[ "$1" == *-mAddSig2760GeVWOSDDB* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConv_Data-WOSDD_B.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConv_MC-WOSDD_B.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConv_MC-WOSDD_B.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConv_MC-WOSDD_B.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mAddSig2760GeVWSDDA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConv_Data-WSDD_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConv_MC-WSDD_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConv_MC-WSDD_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConv_MC-WSDD_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mAddSig2760GeVWSDDB* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConv_Data-WSDD_B.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConv_MC-WSDD_B.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConv_MC-WSDD_B.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConv_MC-WSDD_B.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi    
elif [[ "$1" == *-mAddSig8TeVA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConv_Data_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConv_MC_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConv_MC_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConv_MC_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mAddSig8TeVB* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConv_Data_B.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConv_MC_B.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConv_MC_B.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConv_MC_B.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-mAddSigPbPbLHC13d2A* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC13d2_MC_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_MC_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_MC_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi    
elif [[ "$1" == *-mAddSigPbPbLHC13d2bA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC13d2b_MC_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2b_MC_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2b_MC_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi        
elif [[ "$1" == *-mAddSigPbPbLHC13d2xA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC13d2_LHC13d2b_MC_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_LHC13d2b_MC_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_LHC13d2b_MC_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi        
elif [[ "$1" == *-mAddSigPbPbLHC13d2B* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_B.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC13d2_MC_B.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_MC_B.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_MC_B.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi        
elif [[ "$1" == *-mAddSigPbPbLHC13d2bB* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_B.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC13d2b_MC_B.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2b_MC_B.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2b_MC_B.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi            
elif [[ "$1" == *-mAddSigPbPbLHC13d2xB* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_B.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC13d2_LHC13d2b_MC_B.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_LHC13d2b_MC_B.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_LHC13d2b_MC_B.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi            
elif [[ "$1" == *-mAddSigPbPbLHC13d2bC* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_C.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC13d2b_MC_C.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2b_MC_C.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2b_MC_C.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi            
elif [[ "$1" == *-mAddSigPbPbLHC13d2C* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_C.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC13d2_MC_C.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_MC_C.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_MC_C.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi                
elif [[ "$1" == *-mAddSigPbPbLHC13d2xC* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_C.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC13d2_LHC13d2b_MC_C.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_LHC13d2b_MC_C.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC13d2_LHC13d2b_MC_C.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi                
elif [[ "$1" == *-mAddSigPbPbLHC14a1aA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC14a1a_MC_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC14a1a_MC_Pi0_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC14a1a_MC_Eta_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi                
elif [[ "$1" == *-mAddSigPbPbLHC14a1bA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC14a1b_MC_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC14a1b_MC_Pi0_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC14a1b_MC_Eta_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi                
elif [[ "$1" == *-mAddSigPbPbLHC14a1abA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_LHC14a1a_LHC14a1b_MC_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC14a1a_LHC14a1b_MC_Pi0_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_LHC14a1a_LHC14a1b_MC_Eta_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi                
elif [[ "$1" == *-mAddSigpPbHIJINGA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_A.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_HIJING_MC_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi                    
elif [[ "$1" == *-mAddSigpPbHIJINGGSIA* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_A_B.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_HIJING_MC_A.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_A.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_A.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
        GSIdata=1
    fi                        
elif [[ "$1" == *-mAddSigpPbHIJINGB* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_B.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_HIJING_MC_B.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_B.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_B.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi                        
elif [[ "$1" == *-mAddSigpPbHIJINGGSIB* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_A_B.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_HIJING_MC_B.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_B.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_B.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
        GSIdata=1
    fi                            
elif [[ "$1" == *-mAddSigpPbHIJINGC* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedMinBias/GammaConvV1Data_C.root
    MCRootFile=$DIRECTORY/mergedMinBias/GammaConvV1_HIJING_MC_C.root
    MCRootFileAddSig=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_C.root
    MCRootFileAddSigEta=$DIRECTORY/mergedAddSignal/GammaConvV1_HIJING_MC_C.root
    addedSig=1
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #  exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1 
        MCFILE=0
    fi                        
elif [[ "$1" == *-mAddSig* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedAll/GammaConvV1Data.root
    MCRootFile=$DIRECTORY/mergedAll/GammaConvV1MC.root
    MCRootFileBC=$DIRECTORY/WithoutAddedSignals/GammaConvV1MC.root
    MCRootFileD=$DIRECTORY/WithAddedSignals/GammaConvV1MC.root

    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-m* ]] ; then
    MERGINGMC=1
    DIRECTORY=$2
    Suffix=$3
    DataRootFile=$DIRECTORY/mergedALL/GammaConvV1Data.root
    MCRootFile=$DIRECTORY/mergedALL/GammaConvV1MC.root
    MCRootFileBC=$DIRECTORY/mergedBC/GammaConvV1MC.root
    MCRootFileD=$DIRECTORY/mergedDE/GammaConvV1MC.root

    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
elif [[ "$1" == *-c* ]] ; then
    ONLYCORRECTION=1
    DataRootFile=$2
    Suffix=$3;
elif [[ "$1" == *-d* ]] ; then
    ONLYCORRECTION=1
    ONLYCUTS=1
    DataRootFile=$2
    Suffix=$3;
elif [[ "$1" == *-r* ]] ; then
    ONLYCORRECTION=1
    ONLYRESULTS=1
    DataRootFile=$2
    Suffix=$3;
elif [[ "$1" == *-HI* ]] ; then
    HIRUN=1
    DataRootFile=$2
    MCRootFile=$3
    Suffix=$4;
elif [[ "$1" != -* ]] ; then
    DataRootFile=$1
    MCRootFile=$2
    Suffix=$3;
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
#    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
else 
    DataRootFile=$2
    MCRootFile=$3
    Suffix=$4;
    if [ -f $DataRootFile ]; then
        echo "The data file specified is $DataRootFile"
    else 
        echo "No data file specified, analysis can not be fullfiled."
    #    exit
    fi
    if [ -f $MCRootFile ]; then
        echo "The MC file specified is $MCRootFile"
    else 
        echo "No MC file specified, analysis will only made paritally, please be careful with the results."
        PARTLY=1    
        MCFILE=0
    fi
fi

# ALPHACUTS=0

PERIODNAME="No"

if [ $ONLYCUTS -eq 1 ]; then 
    correct=0
    while [ $correct -eq 0 ]
    do
    echo "Which name should your CutStudies have? None/*name*"
    read answer
    if [ $answer = "None" ]; then
        correct=1
    else
        NAMECUTSTUDIES=$answer
        echo "You have selcted the name: " $NAMECUTSTUDIES;
        correct=1
    fi
    done
    
    correct=0
    while [ $correct -eq 0 ]
    do
    echo "Are these CutStudies for a specific data period? No/*name*"
    read answer
    if [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
        correct=1
    else
        PERIODNAME=$answer
        echo "The period name was set to: " $PERIODNAME;
        correct=1
    fi
    done
fi

correct=0
while [ $correct -eq 0 ]
do
    echo "Which mode are you running? 0 (PCM-PCM), 1 (PCM-Dalitz), 2 (PCM-EMCAL), 3 (PCM-PHOS), 4 (EMCAL-EMCAL), 5 (PHOS-PHOS), 9 (old files), 10 (EMC-merged), 11 (PHOS-merged)"
    read answer
    if [ $answer = "0" ]; then
        echo "You are analysing PCM-PCM output";
        mode=0
        correct=1
    elif [ $answer = "1" ]; then
        echo "You are trying to analyse PCM-Dalitz output, this is the wrong script, please use another one.";
        mode=1
#        AdvMesonQA="AdvancedMesonQA"
        correct=0
    elif [ $answer = "2" ]; then
        echo "You are analysing PCM-EMCAL output";
        mode=2
#        AdvMesonQA="AdvancedMesonQA"
        correct=1
    elif [ $answer = "3" ]; then
        echo "You are analysing PCM-PHOS output";
        mode=3
        AdvMesonQA="AdvancedMesonQA"
        correct=1
    elif [ $answer = "4" ]; then
        echo "You are analysing EMCAL-EMCAL output";
        mode=4
        AdvMesonQA="AdvancedMesonQA"
        correct=1
    elif [ $answer = "5" ]; then
        echo "You are analysing PHOS-PHOS output";
        mode=5
        AdvMesonQA="AdvancedMesonQA"
        correct=1
    elif [ $answer = "10" ]; then
        echo "You are analysing EMC-merged output";
        mode=10
        correct=1
        DoEta=0;
        DoPi0InEtaBinning=0;
    elif [ $answer = "11" ]; then
        echo "You are analysing PHOS-merged output";
        mode=11
        correct=1
        DoEta=0;
        DoPi0InEtaBinning=0;
    elif [ $answer = "9" ]; then
        echo "You are analysing the old output of PCM-PCM";
        mode=9
        correct=1
    else
        echo "Command not found. Please try again.";
    fi
done


correct=0
while [ $correct -eq 0 ]
do
    echo "Do you want to take an already exitsting CutSelection.log-file. Yes/No"
    read answer
    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
        echo "Chosen already existing logfile ...";
        cat CutSelection.log
        correct=1
    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
        if [ $mode = 0 ]; then
            if [ $GSIdata -eq 0 ] ; then
                root -b -q -x -l TaskV1/MakeCutLog.C\(\"$DataRootFile\"\,\"CutSelection.log\"\)
                correct=1
            else 
                root -b -q -x -l TaskV1/MakeCutLog.C\(\"$MCRootFile\"\,\"CutSelection.log\"\)
                correct=1
            fi
        elif [ $mode = 9 ]; then
            if [ $GSIdata -eq 0 ] ; then
                root -b -q -x -l TaskV1/MakeCutLog.C\(\"$DataRootFile\"\,\"CutSelection.log\"\)
                correct=1
            else 
                root -b -q -x -l TaskV1/MakeCutLog.C\(\"$MCRootFile\"\,\"CutSelection.log\"\)
                correct=1
            fi
        elif [ $mode = 2 ]; then 
            if [ $GSIdata -eq 0 ] ; then
                root -b -q -x -l TaskV1/MakeCutLogConvCalo.C\(\"$DataRootFile\"\,\"CutSelection.log\"\)
                correct=1
            else 
                root -b -q -x -l TaskV1/MakeCutLogConvCalo.C\(\"$MCRootFile\"\,\"CutSelection.log\"\)
                correct=1
            fi
        elif [ $mode = 3 ]; then 
            if [ $GSIdata -eq 0 ] ; then
                root -b -q -x -l TaskV1/MakeCutLogConvCalo.C\(\"$DataRootFile\"\,\"CutSelection.log\"\)
                correct=1
            else 
                root -b -q -x -l TaskV1/MakeCutLogConvCalo.C\(\"$MCRootFile\"\,\"CutSelection.log\"\)
                correct=1
            fi
        elif [ $mode = 4 ]; then 
            if [ $GSIdata -eq 0 ] ; then
                root -b -q -x -l TaskV1/MakeCutLogCalo.C\(\"$DataRootFile\"\,\"CutSelection.log\"\)
                correct=1
            else 
                root -b -q -x -l TaskV1/MakeCutLogCalo.C\(\"$MCRootFile\"\,\"CutSelection.log\"\)
                correct=1
            fi
        elif [ $mode = 5 ]; then 
            if [ $GSIdata -eq 0 ] ; then
                root -b -q -x -l TaskV1/MakeCutLogCalo.C\(\"$DataRootFile\"\,\"CutSelection.log\"\)
                correct=1
            else 
                root -b -q -x -l TaskV1/MakeCutLogCalo.C\(\"$MCRootFile\"\,\"CutSelection.log\"\)
                correct=1
            fi
        elif [ $mode = 10 ]; then     
            root -b -q -x -l TaskV1/MakeCutLogCaloMerged.C\(\"$DataRootFile\"\,\"CutSelection.log\"\)
            correct=1
        elif [ $mode = 11 ]; then     
            root -b -q -x -l TaskV1/MakeCutLogCaloMerged.C\(\"$DataRootFile\"\,\"CutSelection.log\"\)
            correct=1
       else 
            echo "mode not correctly set!" 
        fi
    else
        echo "Command not found. Please try again.";
    fi
done

if [ $ONLYCUTS -eq 0 ] && [ $mode -lt 2 ]; then 
    echo "On the top you see all cuts being available, please tell me the standard cut for Meson analysis.";
    read standardCutMeson
    standardCutGamma=$standardCutMeson
    correct=0
    while [ $correct -eq 0 ]
    do
        echo "The standard cut was set to $standardCutMeson. Is this correct? Yes/No?";
        read answer
        if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Continuing ...";
            correct=1
        elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "Aborting ...";
            exit
        else
            echo "Command not found. Please try again.";
        fi
    done
fi
# echo "On the top you see all cuts being available, please tell me the standard cut for Gamma analysis.";
# read standardCutGamma
# 
# correct=0
# while [ $correct -eq 0 ]
# do
#    echo "The standard cut was set to $standardCutGamma. Is this correct? Yes/No?";
#    read answer
#    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
#        echo "Continuing ...";
#        correct=1
#    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
#        echo "Aborting ...";
#        exit
#    else
#        echo "Command not found. Please try again.";
#    fi
# done

correct=0
while [ $correct -eq 0 ]
do
    echo "Which collision system do you want to process? 13TeV (pp@13TeV), 8TeV (pp@8TeV), 7TeV (pp@7TeV), 900GeV (pp@900GeV), 2.76TeV (pp@2.76TeV), PbPb_2.76TeV (PbPb@2.76TeV), pPb_5.023TeV (pPb@5.023TeV)"
    read answer
    if [ $answer = "7TeV" ] || [ $answer = "7" ]; then
        energy="7TeV";
    elif [ $answer = "8TeV" ] || [ $answer = "8" ]; then
        energy="8TeV";
    elif [ $answer = "13TeV" ] || [ $answer = "13" ]; then
        energy="13TeV";
    elif [ $answer = "900GeV" ] || [ $answer = "900" ] || [ $answer = "9" ] || [ $answer = "0.9" ]; then
        energy="900GeV";
    elif [ $answer = "2.76TeV" ] || [ $answer = "2" ] || [ $answer = "2.76" ]; then
        energy="2.76TeV";
    elif [ $answer = "PbPb_2.76TeV" ] || [ $answer = "PbPb_2.76" ] || [ $answer = "PbPb2" ] || [ $answer = "Pb2" ]; then
        energy="PbPb_2.76TeV";
    elif [ $answer = "pPb_5.023TeV" ] || [ $answer = "pPb_5.023" ] || [ $answer = "pPb5" ];  then
        energy="pPb_5.023TeV";
    fi
    echo "The collision system has been selected to be $energy."
    
    if [ $energy = "7TeV" ]; then
        echo "Do you want to produce Direct Photon plots? Yes/No?";
        read answer
        if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Will produce Direct Photon plots ...";
            directphoton="directPhoton"
            Con=1
            if [ $ONLYCORRECTION -eq 0 ]; then
                GiveBinningDirectPhoton7TeV
                correctPi0=1
                correctEta=1
            fi
            if [ $correctPi0 -eq 0 ]; then
                correct=0
            elif [ $correctEta -eq 0 ]; then
                correct=0
            else 
                correct=1
            fi
        elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "No Direct Photon plots will be produced ...";
            Conference="No"
            Con=0
            if [ $ONLYCORRECTION -eq 0 ]; then
                GiveBinning7TeV
                correctPi0=1
                correctEta=1
            fi
            if [ $correctPi0 -eq 0 ]; then
                correct=0    
            elif [ $correctEta -eq 0 ]; then
                correct=0
            else 
                correct=1
            fi
        else
            echo "Command not found. Please try again.";
        fi
    elif [ $energy = "8TeV" ]; then
        Conference="No"
        Con=0
        if [ $ONLYCORRECTION -eq 0 ]; then
            GiveBinning8TeV
            correctPi0=1
            correctEta=1
        fi
        if [ $correctPi0 -eq 0 ]; then
            correct=0    
        elif [ $correctEta -eq 0 ]; then
            correct=0
        else 
            correct=1
        fi
    elif [ $energy = "13TeV" ]; then
        Conference="No"
        Con=0
        DoGamma=0
        if [ $mode -ne 0 ]; then
            echo "Mode is set to PCM-PCM";
            mode=0
        fi
        if [ $ONLYCORRECTION -eq 0 ]; then
            GiveBinning13TeV
            correctPi0=1
            correctEta=1
        fi
        if [ $correctPi0 -eq 0 ]; then
            correct=0    
        elif [ $correctEta -eq 0 ]; then
            correct=0
        else 
            correct=1
        fi
    elif [ $energy = "900GeV" ]; then
        echo "Do you want to produce Direct Photon plots? Yes/No?";
        read answer
        if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Will produce Direct Photon plots ...";
            directphoton="directPhoton"
            Con=1
            if [ $ONLYCORRECTION -eq 0 ]; then
                GiveBinningDirectPhoton900GeV
                correctPi0=1
                correctEta=1
            fi
            if [ $correctPi0 -eq 0 ]; then
                correct=0
            elif [ $correctEta -eq 0 ]; then
                correct=0
            else 
                correct=1
            fi
        elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "No Direct Photon plots will be produced ...";
            directphoton="No"
            Con=0
            if [ $ONLYCORRECTION -eq 0 ]; then
                GiveBinning900GeV
                correctPi0=1
                correctEta=1
            fi
            if [ $correctPi0 -eq 0 ]; then
                correct=0
            elif [ $correctEta -eq 0 ]; then
                correct=0
            else 
                correct=1
            fi
        else
            echo "Command not found. Please try again.";
        fi
    elif [ $energy = "2.76TeV" ]; then
        if [ $mode -eq 10 ] || [ $mode -eq 11 ]; then 
            if [ $ONLYCORRECTION -eq 0 ]; then
                GiveBinning2760GeVMerged
                correctPi0=1
                correctEta=1
            fi
            if [ $correctPi0 -eq 0 ]; then
                correct=0
            elif [ $correctEta -eq 0 ]; then
                correct=0
            else 
                correct=1
            fi
        else 
#             echo "Do you want to produce Direct Photon plots? Yes/No?";
#             read answer
#             if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
#                 echo "Will produce Direct Photon plots ...";
#                 directphoton="directPhoton"
#                 Con=1
#                 if [ $ONLYCORRECTION -eq 0 ]; then
#                     GiveBinningDirectPhoton2760TeV
#                     correctPi0=1
#                     correctEta=1
#                 fi
#                 if [ $correctPi0 -eq 0 ]; then
#                     correct=0
#                 elif [ $correctEta -eq 0 ]; then
#                     correct=0
#                 else 
#                     correct=1
#                 fi
#             elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
                echo "No Direct Photon plots will be produced ...";
                directphoton="No"
                Con=0
                if [ $ONLYCORRECTION -eq 0 ]; then
                    GiveBinning2760GeV
                    correctPi0=1
                    correctEta=1
                fi
                if [ $correctPi0 -eq 0 ]; then
                    correct=0
                elif [ $correctEta -eq 0 ]; then
                    correct=0
                else 
                    correct=1
                fi
#             else
#                 echo "Command not found. Please try again.";
#             fi

            if [ $ONLYRESULTS -eq 0 ]; then
                if [ $ONLYCORRECTION -eq 0 ];  then
                    echo "Do you want to use THnSparse for the background? Yes/No?";
                    read answer
                    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
                        echo "Will use THnSparse for the background ...";
                        useTHnSparse=1
                    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
                        echo "Will NOT use THnSparse for the background ...";
                        useTHnSparse=0
                    else
                        echo "Command not found. Please try again.";
                    fi
                fi
            fi
        fi
    elif [ $energy = "PbPb_2.76TeV" ]; then
        echo "Do you want to produce Direct Photon plots? Yes/No?";
        read answer
        if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Will produce Direct Photon plots ...";
            directphoton="directPhoton"
            Con=1
            if [ $ONLYCORRECTION -eq 0 ]; then
                GiveBinningDirectPhotonHI
                correctPi0=1
                correctEta=1
            fi
            if [ $correctPi0 -eq 0 ]; then
                correct=0
            elif [ $correctEta -eq 0 ]; then
                correct=0
            else 
                correct=1
            fi
        elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "No Direct Photon plots will be produced ...";
            directphoton="No"
            Con=0
            if [ $ONLYCORRECTION -eq 0 ]; then
                GiveBinningHI
                correctPi0=1
                correctEta=1
            else 
                correctPi0=1
                correctEta=1
            fi
            
            if [ $correctPi0 -eq 0 ]; then
                correct=0
            elif [ $correctEta -eq 0 ]; then
                correct=0
            else 
                correct=1
            fi
        else
            echo "Command not found. Please try again.";
        fi

        if [ $ONLYRESULTS -eq 0 ]; then
            if [ $ONLYCORRECTION -eq 0 ];  then
                echo "Do you want to use THnSparse for the background? Yes/No?";
                read answer
                if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
                    echo "Will use THnSparse for the background ...";
                    useTHnSparse=1
                elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
                    echo "Will NOT use THnSparse for the background ...";
                    useTHnSparse=0
                else
                    echo "Command not found. Please try again.";
                fi
            fi    
        fi
        
    elif [ $energy = "pPb_5.023TeV" ]; then
        directphoton="No"
        Con=0
        if [ $ONLYCORRECTION -eq 0 ]; then
            GiveBinningpPb
            correctPi0=1
            correctEta=1
        fi
        if [ $correctPi0 -eq 0 ]; then
            correct=0
        elif [ $correctEta -eq 0 ]; then
            correct=0
        else 
            correct=1
        fi

        if [ $mode = 2 ] || [ $mode = 3 ] || [ $mode = 4 ] || [ $mode = 5 ]; then 
            useTHnSparse=0
        fi 
        
        correct=0
        while [ $correct -eq 0 ]
        do
            echo "Do you want to use MinBias Efficiencies only? Yes/No?";
            read answer
            if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
                OPTMINBIASEFF="MinBiasEffOnly"
                echo "Calculating MinBias Efficiecy only ...";
                correct=1
            elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
                OPTMINBIASEFF=""
                echo "Nothing to be done ...";
                correct=1
            else
                echo "Command not found. Please try again.";
            fi
        done
    fi
done

if [ $mode -eq 0 ] || [ $mode -eq 9 ]; then 
    correct=0
    while [ $correct -eq 0 ]
    do
        echo "Please don't forget to run the TaskV1/AnalyseDCATestV1.C separately to estimate train pileup?";
        echo "Do the output of this macro exist already? Yes/No?";
        read answer
        if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            ESTIMATEPILEUP="EstimateTrainPileUp"
            echo "Running with additional histos ...";
            correct=1
        elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            ESTIMATEPILEUP=""
            echo "Running in Normal mode ...";
            correct=1
        else
            echo "Command not found. Please try again.";
        fi
    done
fi 

echo "mode has been chosen: $mode "

if [ $mode -lt 10 ]; then 
    echo "I went into standard modes";
    if [ $ONLYRESULTS = 0 ] ; then
        if [ $ONLYCORRECTION -eq 0 ];  then
    #        echo "Extraction will be done using modified Gaussian.";
    #        crystal=Gaussian

            correct=0
            while [ $correct -eq 0 ]
            do
                echo "Which fit do you want to do? CrystalBall or gaussian convoluted with an exponential function? CrystalBall/Gaussian?";
                read answer
                if [ $answer = "CrystalBall" ] || [ $answer = "C" ] || [ $answer = "c" ]; then
                    echo "CrystalBall chosen ...";
                    correct=1
                    crystal=CrystalBall
                elif [ $answer = "Gaussian" ] || [ $answer = "G" ] || [ $answer = "g" ]; then
                    echo "Gaussian chosen ...";
                    correct=1    
                    crystal=Gaussian
                else
                    echo "Command not found. Please try again.";
                fi
            done
        fi
        
    #    echo "Hauptroutine stimmt" 
        correct=0
        while [ $correct -eq 0 ]
        do
            echo "Please check that you really want to process all cuts, otherwise change the CutSelection.log. Remember at first all gamma cutstudies will be carried out. Make sure that the standard cut is the first in the file. Continue? Yes/No?";
            read answer
            if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
                echo "Continuing ...";
                correct=1
            elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
                echo "Aborting ...";
                exit
            else
                echo "Command not found. Please try again.";
            fi
        done

        echo $DoPi0
        echo $DoPi0InEtaBinning
        echo $DoEta
    #Read the different cuts form the Cut selection log file
        CutSelections=`cat CutSelection.log`
        for cutSelection in $CutSelections; do
            if [ -d $cutSelection ]; then
                echo "CutSelection $cutSelection directory already exists, all files will be overwritten ";
                mkdir $cutSelection/$energy
            else
                mkdir $cutSelection
                mkdir $cutSelection/$energy
            fi

            if [ $ONLYCUTS -eq 0 ]; then 
                if [ -d $cutSelection/$energy/$Suffix ]; then
                    echo "Graphical Output $Suffix directory already exists, all files will be overwritten ";
                else
                    mkdir $cutSelection/$energy/$Suffix
                fi

                if [ $ONLYCORRECTION -eq 0 ]; then            
                    echo "CutSelection is $cutSelection";
                    if [ $DoPi0 -eq 1 ]; then
                        optionsPi0Data=\"Pi0\"\,\"$DataRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kFALSE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtPi0\,kFALSE
                        if [ -f $DataRootFile ]; then 
                            ExtractSignal $optionsPi0Data
                        fi
                        Pi0dataRAWFILE=`ls $cutSelection/$energy/Pi0_data_GammaConvV1WithoutCorrection_*.root`             
                        if [ $MCFILE -eq 1 ]; then 
                            optionsPi0MC=\"Pi0\"\,\"$MCRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtPi0\,kFALSE 
                            ExtractSignal $optionsPi0MC
                            Pi0MCRAWFILE=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1WithoutCorrection_*.root`
                            Pi0MCcorrectionFILE=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistos_*.root`
                            if [ $MERGINGMC -eq 1 ]; then
                                if [ $addedSig -eq 1 ]; then
                                    optionsPi0MC2=\"Pi0\"\,\"$MCRootFileAddSig\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"AddSig\"\,\"$AdvMesonQA\"\,$BinsPtPi0\,kTRUE    
                                    ExtractSignal $optionsPi0MC2
                                    Pi0MCcorrection=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistos_*.root`
                                    Pi0MCcorrectionAddSig=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistosAddSig_*.root`
                                    root -b -x -q -l TaskV1/MergeEffiWithProperWeighting2760GeV.C\+\(\"$cutSelection\"\,\"Pi0\"\,\"$Suffix\"\,\"$energy\"\,\"$Pi0MCcorrection\"\,\"$cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistosMinBias_$cutSelection.root\"\,\"$Pi0MCcorrectionAddSig\"\)
                                elif [ $addedSig -eq 2 ]; then
                                    optionsPi0MC2=\"Pi0\"\,\"$MCRootFileAddSig\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"JetJetMC\"\,\"$AdvMesonQA\"\,$BinsPtPi0\,kFALSE               
                                    ExtractSignal $optionsPi0MC2
                                    Pi0MCcorrection=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistos_*.root`
                                    Pi0MCcorrectionAddSig=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistosJetJetMC_*.root`
                                    root -b -x -q -l TaskV1/MergeEffiJetJetMC.C\+\(\"$cutSelection\"\,\"Pi0\"\,\"$Suffix\"\,\"$energy\"\,\"$Pi0MCcorrection\"\,\"$cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistosMinBias_$cutSelection.root\"\,\"$Pi0MCcorrectionAddSig\"\,$minPtMergePi0\)

                                else 
                                    optionsPi0MCBC=\"Pi0\"\,\"$MCRootFileBC\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"BC\"\,\"$AdvMesonQA\"\,$BinsPtPi0\,kFALSE
                                    echo $optionsPi0MCBC
                                    ExtractSignal $optionsPi0MCBC
                                    optionsPi0MCDE=\"Pi0\"\,\"$MCRootFileD\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"D\"\,\"$AdvMesonQA\"\,$BinsPtPi0\,kFALSE
                                    echo $optionsPi0MCDE
                                    ExtractSignal $optionsPi0MCDE
                                    Pi0MCcorrectionBCFILE=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistosBC_*.root`
                                    Pi0MCcorrectionDFILE=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistosD_*.root`
                                    root -x -q -l -b  TaskV1/MergeEffiWithProperWeighting.C\(\"$DIRECTORY\"\,\"$cutSelection\"\,\"Pi0\",\"$Suffix\"\,\"$energy\"\,\"$Pi0MCcorrectionFILE\"\,\"$Pi0MCcorrectionBCFILE\",\"$Pi0MCcorrectionDFILE\"\)
                                fi
                            fi
                            
                            root -x -l -b -q TaskV1/LineShape.C\+\(\"$Pi0dataRAWFILE\"\,\"$Pi0MCRAWFILE\"\,\"$cutSelection\"\,\"Pi0\"\,\"$Suffix\"\,\"$energy\"\,$BinsPtPi0\,$mode\)
                        fi    
                    fi
                    if [ $DoGamma -eq 1 ]; then
                        optionsPi0Data=\"Pi0\"\,\"$DataRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kFALSE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"\"\,\"$ESTIMATEPILEUP\"\,$BinsPtPi0
                        if [ $NEWGammaMacros == 0 ]; then
                            ExtractSignalGamma $optionsPi0Data
                        else 
                            optionsPi0Data=\"Pi0\"\,\"$DataRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kFALSE\"\,\"$energy\"\,\"$directphoton\"\,\"\"\,$BinsPtPi0
                            ExtractSignalGammaV2 $optionsPi0Data
                        fi
                        if [ $MCFILE -eq 1 ]; then 
                            optionsPi0MC=\"Pi0\"\,\"$MCRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"\"\,\"$ESTIMATEPILEUP\"\,$BinsPtPi0 
                            if [ $NEWGammaMacros == 0 ]; then
                                ExtractSignalGamma $optionsPi0MC
                            else 
                                optionsPi0MC=\"Pi0\"\,\"$MCRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$directphoton\"\,\"\"\,$BinsPtPi0 
                                ExtractSignalGammaV2 $optionsPi0MC
                            fi
                        fi    
                    fi
                    
                    if [ $DoPi0InEtaBinning -eq 1 ]; then
                        if [ -f $DataRootFile ]; then 
                            root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Pi0EtaBinning\"\,\"$DataRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kFALSE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)               
                        fi 
                        Pi0EtadataRAWFILE=`ls $cutSelection/$energy/Pi0EtaBinning_data_GammaConvV1WithoutCorrection_*.root`
                        if [ $MCFILE -eq 1 ]; then 
                            root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Pi0EtaBinning\"\,\"$MCRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)           
                            Pi0EtaMCRAWFILE=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1WithoutCorrection_*.root`   
                            Pi0EtaMCcorrectionFILE=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistos_*.root`
                            if [ $MERGINGMC -eq 1 ]; then
                                if [ $addedSig -eq 1 ]; then
                                    root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Pi0EtaBinning\"\,\"$MCRootFileAddSig\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"AddSig\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kTRUE\,$mode\,$useTHnSparse\)
                                    Pi0EtaMCcorrection=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistos_*.root`
                                    Pi0EtaMCcorrectionAddSig=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistosAddSig_*.root`
                                    root -b -x -q -l TaskV1/MergeEffiWithProperWeighting2760GeV.C\+\(\"$cutSelection\"\,\"Pi0EtaBinning\"\,\"$Suffix\"\,\"$energy\"\,\"$Pi0EtaMCcorrection\"\,\"$cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistosMinBias_$cutSelection.root\"\,\"$Pi0EtaMCcorrectionAddSig\"\)
                                elif [ $addedSig -eq 2 ]; then
                                    root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Pi0EtaBinning\"\,\"$MCRootFileAddSig\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"JetJetMC\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)
                                    Pi0EtaMCcorrection=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistos_*.root`
                                    Pi0EtaMCcorrectionAddSig=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistosJetJetMC_*.root`
                                    root -b -x -q -l TaskV1/MergeEffiJetJetMC.C\+\(\"$cutSelection\"\,\"Pi0EtaBinning\"\,\"$Suffix\"\,\"$energy\"\,\"$Pi0EtaMCcorrection\"\,\"$cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistosMinBias_$cutSelection.root\"\,\"$Pi0EtaMCcorrectionAddSig\"\,$minPtMergePi0\)

                                else 
                                    root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Pi0EtaBinning\"\,\"$MCRootFileBC\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"BC\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)          
                                    root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Pi0EtaBinning\"\,\"$MCRootFileD\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"D\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)          
                                    Pi0EtaMCcorrectionBCFILE=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistosBC_*.root`
                                    Pi0EtaMCcorrectionDFILE=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistosD_*.root`
                                    root -x -q -l -b  TaskV1/MergeEffiWithProperWeighting.C\(\"$DIRECTORY\"\,\"$cutSelection\"\,\"Pi0EtaBinning\",\"$Suffix\"\,\"$energy\"\,\"$Pi0EtaMCcorrectionFILE\"\,\"$Pi0EtaMCcorrectionBCFILE\",\"$Pi0EtaMCcorrectionDFILE\"\)
                                fi
                            fi
                            
                            root -x -l -b -q TaskV1/LineShape.C\+\(\"$Pi0EtadataRAWFILE\"\,\"$Pi0EtaMCRAWFILE\"\,\"$cutSelection\"\,\"Pi0EtaBinning\"\,\"$Suffix\"\,\"$energy\"\,$BinsPtEta\,$mode\)
                        fi
                    fi    
                    if [ $DoEta -eq 1 ]; then
                        if [ -f $DataRootFile ]; then 
                            root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Eta\"\,\"$DataRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kFALSE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)               
                        fi
                        EtadataRAWFILE=`ls $cutSelection/$energy/Eta_data_GammaConvV1WithoutCorrection_*.root`        
                        if [ $MCFILE -eq 1 ]; then 
                            root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Eta\"\,\"$MCRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)               
                            EtaMCRAWFILE=`ls $cutSelection/$energy/Eta_MC_GammaConvV1WithoutCorrection_*.root`
                            EtaMCcorrectionFILE=`ls $cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistos_*.root`
                            
                            if [ $MERGINGMC -eq 1 ]; then
                                if [ $addedSig -eq 1 ]; then
                                    root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Eta\"\,\"$MCRootFileAddSigEta\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"AddSig\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kTRUE\,$mode\,$useTHnSparse\)
                                    EtaMCcorrection=`ls $cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistos_*.root`
                                    EtaMCcorrectionAddSig=`ls $cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistosAddSig_*.root`
                                    root -b -x -q -l TaskV1/MergeEffiWithProperWeighting2760GeV.C\+\(\"$cutSelection\"\,\"Eta\"\,\"$Suffix\"\,\"$energy\"\,\"$EtaMCcorrection\"\,\"$cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistosMinBias_$cutSelection.root\"\,\"$EtaMCcorrectionAddSig\"\)
                                elif [ $addedSig -eq 2 ]; then
                                    root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Eta\"\,\"$MCRootFileAddSig\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"JetJetMC\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)
                                    EtaMCcorrection=`ls $cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistos_*.root`
                                    EtaMCcorrectionAddSig=`ls $cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistosJetJetMC_*.root`
                                    root -b -x -q -l TaskV1/MergeEffiJetJetMC.C\+\(\"$cutSelection\"\,\"Eta\"\,\"$Suffix\"\,\"$energy\"\,\"$EtaMCcorrection\"\,\"$cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistosMinBias_$cutSelection.root\"\,\"$EtaMCcorrectionAddSig\"\,$minPtMergeEta\)    
                                else 
                                    root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Eta\"\,\"$MCRootFileBC\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"BC\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)               
                                    root -x -q -l -b  TaskV1/ExtractSignalV2.C\+\(\"Eta\"\,\"$MCRootFileD\"\,\"$cutSelection\"\,\"$Suffix\"\,\"kTRUE\"\,\"$energy\"\,\"$crystal\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"D\"\,\"$AdvMesonQA\"\,$BinsPtEta\,kFALSE\,$mode\,$useTHnSparse\)               
                                    EtaMCcorrectionBCFILE=`ls $cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistosBC_*.root`
                                    EtaMCcorrectionDFILE=`ls $cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistosD_*.root`
                                
                                    root -x -q -l -b  TaskV1/MergeEffiWithProperWeighting.C\(\"$DIRECTORY\"\,\"$cutSelection\"\,\"Eta\",\"$Suffix\"\,\"$energy\"\,\"$EtaMCcorrectionFILE\"\,\"$EtaMCcorrectionBCFILE\",\"$EtaMCcorrectionDFILE\"\)
                                fi
                            fi
                            root -x -l -b -q TaskV1/LineShape.C\+\(\"$EtadataRAWFILE\"\,\"$EtaMCRAWFILE\"\,\"$cutSelection\"\,\"Eta\"\,\"$Suffix\"\,\"$energy\"\,$BinsPtEta\,$mode\)
                        fi
                    fi 
                fi
                
                Pi0dataRAWFILE=`ls $cutSelection/$energy/Pi0_data_GammaConvV1WithoutCorrection_*$cutSelection*.root`             
                Pi0MCRAWFILE=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1WithoutCorrection_*$cutSelection*.root`
                Pi0MCcorrectionFILE=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1CorrectionHistos_*$cutSelection*.root`
                Pi0EtadataRAWFILE=`ls $cutSelection/$energy/Pi0EtaBinning_data_GammaConvV1WithoutCorrection_*$cutSelection*.root`
                Pi0EtaMCRAWFILE=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1WithoutCorrection_*$cutSelection*.root`   
                Pi0EtaMCcorrectionFILE=`ls $cutSelection/$energy/Pi0EtaBinning_MC_GammaConvV1CorrectionHistos_*$cutSelection*.root`
                EtadataRAWFILE=`ls $cutSelection/$energy/Eta_data_GammaConvV1WithoutCorrection_*$cutSelection*.root`
                EtaMCRAWFILE=`ls $cutSelection/$energy/Eta_MC_GammaConvV1WithoutCorrection_*$cutSelection*.root`
                EtaMCcorrectionFILE=`ls $cutSelection/$energy/Eta_MC_GammaConvV1CorrectionHistos_*$cutSelection*.root`

                if [ $DoPi0 -eq 1 ]; then
                    if [ -f $Pi0dataRAWFILE ] && [ -f $Pi0MCcorrectionFILE ]; then
                        CorrectSignal $Pi0dataRAWFILE $Pi0MCcorrectionFILE $cutSelection $Suffix Pi0 kFALSE $ESTIMATEPILEUP $directphoton 
                    else 
                        PARTLY=1
                    fi
                    if [ -f $Pi0MCRAWFILE ] && [ -f $Pi0MCcorrectionFILE ]; then
                        CorrectSignal $Pi0MCRAWFILE $Pi0MCcorrectionFILE $cutSelection $Suffix Pi0 kTRUE $ESTIMATEPILEUP $directphoton 
                    else 
                        PARTLY=1
                    fi
                fi
                
                if [ $DoGamma -eq 1 ]; then
                    if [ -f $Pi0dataRAWFILE ] && [ -f $Pi0MCcorrectionFILE ]; then
                        if [ $NEWGammaMacros == 0 ]; then
                            CorrectSignalGamma $Pi0dataRAWFILE $Pi0MCcorrectionFILE $cutSelection $Suffix Pi0 kFALSE
                        else 
                            CorrectSignalGammaV2 $Pi0dataRAWFILE $Pi0MCcorrectionFILE $cutSelection $Suffix Pi0 kFALSE
                        fi
                        
                    else 
                        PARTLY=1
                    fi
                    if [ -f $Pi0MCRAWFILE ] && [ -f $Pi0MCcorrectionFILE ]; then
                        if [ $NEWGammaMacros == 0 ]; then
                            CorrectSignalGamma $Pi0MCRAWFILE $Pi0MCcorrectionFILE $cutSelection $Suffix Pi0 kTRUE
                        else 
                            CorrectSignalGammaV2 $Pi0MCRAWFILE $Pi0MCcorrectionFILE $cutSelection $Suffix Pi0 kTRUE
                        fi
                    else 
                        PARTLY=1
                    fi
                    Pi0dataCorr=`ls $cutSelection/$energy/Pi0_data_GammaConvV1Correction_*.root`
                    GammaPi0dataCorr=`ls $cutSelection/$energy/Gamma_Pi0_data_GammaConvV1Correction_*.root`
                    if [ $NEWGammaMacros == 0 ]; then 
                        CreateGammaFinalResults $GammaPi0dataCorr $Pi0dataCorr $cutSelection $Suffix Pi0 kFALSE;
                    fi    
    #                Pi0MCCorr=`ls $cutSelection/$energy/Pi0_MC_GammaConvV1Correction_*.root`
    #                GammaPi0MCCorr=`ls $cutSelection/$energy/Gamma_Pi0_MC_GammaConvV1Correction_*.root`
    #                CreateGammaFinalResults $GammaPi0MCCorr $Pi0MCCorr $cutSelection $Suffix Pi0 kTRUE;
                fi
                
                if [ $DoPi0InEtaBinning -eq 1 ]; then    
                    if [ -f $Pi0EtadataRAWFILE ] && [ -f $Pi0EtaMCcorrectionFILE ] ; then
                        CorrectSignal $Pi0EtadataRAWFILE $Pi0EtaMCcorrectionFILE $cutSelection $Suffix Pi0EtaBinning kFALSE $ESTIMATEPILEUP $directphoton 
                    else 
                            PARTLY=1
                    fi
                    if [ -f $Pi0EtaMCRAWFILE ] && [ -f $Pi0EtaMCcorrectionFILE ] ; then
                        CorrectSignal $Pi0EtaMCRAWFILE $Pi0EtaMCcorrectionFILE $cutSelection $Suffix Pi0EtaBinning kTRUE $ESTIMATEPILEUP $directphoton 
                    else 
                            PARTLY=1
                    fi
                fi
                if [ $DoEta -eq 1 ]; then    
                    if [ -f $EtadataRAWFILE ] && [ -f $EtaMCcorrectionFILE ]; then
                        CorrectSignal $EtadataRAWFILE $EtaMCcorrectionFILE $cutSelection $Suffix Eta kFALSE $ESTIMATEPILEUP $directphoton 
                    else 
                            PARTLY=1
                    fi
                    if [ -f $EtaMCRAWFILE ] && [ -f $EtaMCcorrectionFILE ]; then
                            CorrectSignal $EtaMCRAWFILE $EtaMCcorrectionFILE $cutSelection $Suffix Eta kTRUE $ESTIMATEPILEUP $directphoton 
                    else 
                            PARTLY=1
                    fi

                fi
            fi
            NORMALCUTS=`expr $NORMALCUTS + 1`
        done
        
        if [ $NEWGammaMacros == 1 ]; then
            if [ $DoGamma == 1 ]; then
                root -x -q -l -b TaskV1/GammaCutStudiesV3.C\+\(\"CutSelection.log\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,\"$Suffix\"\,$mode\)
            fi
            DoGamma=0;
        fi
        if [ $DoPi0 -eq 1 ]; then
            root -x -q -l -b TaskV1/CutStudiesOverview.C\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Pi0\"\,\"kFALSE\"\,\"$OPTMINBIASEFF\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,$DoGamma\,\"\"\,\"$PERIODNAME\"\,$mode\)
            root -x -q -l -b TaskV1/CutStudiesOverview.C\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Pi0\"\,\"kTRUE\"\,\"$OPTMINBIASEFF\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,$DoGamma\,\"\"\,\"$PERIODNAME\"\,$mode\)
        fi
        if [ $DoPi0InEtaBinning -eq 1 ]; then
            root -x -q -l -b TaskV1/CutStudiesOverview.C\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Pi0EtaBinning\"\,\"kFALSE\"\,\"$OPTMINBIASEFF\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,0\,\"\"\,\"$PERIODNAME\"\,$mode\)
            root -x -q -l -b TaskV1/CutStudiesOverview.C\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Pi0EtaBinning\"\,\"kTRUE\"\,\"$OPTMINBIASEFF\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,0\,\"\"\,\"$PERIODNAME\"\,$mode\)
        fi
        if [ $DoEta -eq 1 ]; then
            root -x -q -l -b TaskV1/CutStudiesOverview.C\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Eta\"\,\"kFALSE\"\,\"$OPTMINBIASEFF\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,0\,\"\"\,\"$PERIODNAME\"\,$mode\)
            root -x -q -l -b TaskV1/CutStudiesOverview.C\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Eta\"\,\"kTRUE\"\,\"$OPTMINBIASEFF\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,0\,\"\"\,\"$PERIODNAME\"\,$mode\)
        fi
    fi        
else
    if [ $ONLYRESULTS -eq 0 ]; then
        correct=0
        while [ $correct -eq 0 ]
        do
            echo "Please check that you really want to process all cuts, otherwise change the CutSelection.log. Make sure that the standard cut is the first in the file. Continue? Yes/No?";
            read answer
            if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
                echo "Continuing ...";
                correct=1
            elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
                echo "Aborting ...";
                exit
            else
                echo "Command not found. Please try again.";
            fi
        done

        echo $DoPi0
        echo $DoEta
        #Read the different cuts form the Cut selection log file
        CutSelections=`cat CutSelection.log`
        for cutSelection in $CutSelections; do
            if [ -d $cutSelection ]; then
                echo "CutSelection $cutSelection directory already exists, all files will be overwritten ";
                mkdir $cutSelection/$energy
            else
                mkdir $cutSelection
                mkdir $cutSelection/$energy
            fi

            if [ $ONLYCUTS -eq 0 ]; then 
                if [ -d $cutSelection/$energy/$Suffix ]; then
                    echo "Graphical Output $Suffix directory already exists, all files will be overwritten ";
                else
                    mkdir $cutSelection/$energy/$Suffix
                fi

                if [ $ONLYCORRECTION -eq 0 ]; then            
                    echo "CutSelection is $cutSelection";
                    if [ $DoPi0 -eq 1 ]; then
                        if [ -f $DataRootFile ]; then 
                            root -b -x -q -l TaskV1/ExtractSignalMergedMeson.C\+\+\(\"Pi0\"\,\"$DataRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,kFALSE\,\"$energy\"\,\"Gaussian\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtPi0\,$mode\)
                        fi
                        Pi0dataRAWFILE=`ls $cutSelection/$energy/Pi0_data_GammaMergedWithoutCorrection_*.root`             
                        if [ $MCFILE -eq 1 ]; then 
                            root -b -x -q -l TaskV1/ExtractSignalMergedMeson.C\+\+\(\"Pi0\"\,\"$MCRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,kTRUE\,\"$energy\"\,\"Gaussian\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtPi0\,$mode\)
                            Pi0MCRAWFILE=`ls $cutSelection/$energy/Pi0_MC_GammaMergedWithoutCorrection_*.root`
                            Pi0MCcorrectionFILE=`ls $cutSelection/$energy/Pi0_MC_GammaMergedCorrectionHistos_*.root`
                            if [ $MERGINGMC -eq 1 ]; then 
                                root -b -x -q -l TaskV1/ExtractSignalMergedMeson.C\+\+\(\"Pi0\"\,\"$MCRootFileGJ\"\,\"$cutSelection\"\,\"$Suffix\"\,kTRUE\,\"$energy\"\,\"Gaussian\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtPi0\,$mode\,1\)
                                Pi0MCcorrectionFILEJJG=`ls $cutSelection/$energy/Pi0_MC_GammaMergedCorrectionHistosJJGammaTrigg_*.root`
                                root -b -x -q -l TaskV1/MergeCorrFactorsJJandJJGammaTrigMergedCluster.C\+\(\"$cutSelection\"\,\"Pi0\"\,\"$Suffix\"\,\"$energy\"\,\"$Pi0MCcorrectionFILE\"\,\"$cutSelection/$energy/Pi0_MC_GammaMergedCorrectionHistosJJ_$cutSelection.root\"\,\"$Pi0MCcorrectionFILEJJG\"\)
                                
                            fi
                        fi    
                    fi
                    
                    if [ $DoEta -eq 1 ]; then
                        if [ -f $DataRootFile ]; then 
                            root -b -x -q -l TaskV1/ExtractSignalMergedMeson.C\+\+\(\"Eta\"\,\"$DataRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,kFALSE\,\"$energy\"\,\"Gaussian\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtEta\,$mode\)
                        fi
                        EtadataRAWFILE=`ls $cutSelection/$energy/Eta_data_GammaMergedWithoutCorrection_*.root`        
                        if [ $MCFILE -eq 1 ]; then 
                            root -b -x -q -l TaskV1/ExtractSignalMergedMeson.C\+\+\(\"Eta\"\,\"$MCRootFile\"\,\"$cutSelection\"\,\"$Suffix\"\,kTRUE\,\"$energy\"\,\"Gaussian\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtEta\,$mode\)
                            EtaMCRAWFILE=`ls $cutSelection/$energy/Eta_MC_GammaMergedWithoutCorrection_*.root`
                            EtaMCcorrectionFILE=`ls $cutSelection/$energy/Eta_MC_GammaMergedCorrectionHistos_*.root`
                            if [ $MERGINGMC -eq 1 ]; then 
                                root -b -x -q -l TaskV1/ExtractSignalMergedMeson.C\+\+\(\"Eta\"\,\"$MCRootFileGJ\"\,\"$cutSelection\"\,\"$Suffix\"\,kTRUE\,\"$energy\"\,\"Gaussian\"\,\"\"\,\"$AdvMesonQA\"\,$BinsPtEta\,$mode\,1\)
                            fi

                        fi
                    fi 
                fi
                
                if [ $DoPi0 -eq 1 ]; then
                    Pi0dataRAWFILE=`ls $cutSelection/$energy/Pi0_data_GammaMergedWithoutCorrection_$cutSelection*.root`             
                    Pi0MCRAWFILE=`ls $cutSelection/$energy/Pi0_MC_GammaMergedWithoutCorrection_$cutSelection*.root`
                    Pi0MCcorrectionFILE=`ls $cutSelection/$energy/Pi0_MC_GammaMergedCorrectionHistos_$cutSelection*.root`
                fi    
                if [ $DoEta -eq 1 ]; then
                    EtadataRAWFILE=`ls $cutSelection/$energy/Eta_data_GammaMergedWithoutCorrection_$cutSelection*.root`
                    EtaMCRAWFILE=`ls $cutSelection/$energy/Eta_MC_GammaMergedWithoutCorrection_$cutSelection*.root`
                    EtaMCcorrectionFILE=`ls $cutSelection/$energy/Eta_MC_GammaMergedCorrectionHistos_$cutSelection*.root`
                fi
                
                if [ $DoPi0 -eq 1 ]; then
                    if [ -f $Pi0dataRAWFILE ] && [ -f $Pi0MCcorrectionFILE ]; then
                          root -b -x -q -l TaskV1/CorrectSignalMerged.C\+\+\(\"$Pi0dataRAWFILE\"\,\"$Pi0MCcorrectionFILE\"\,\"$cutSelection\"\,\"$Suffix\"\,\"Pi0\"\,kFALSE\,\"$energy\"\,\"$PERIODNAME\"\,10\)
                    else 
                        PARTLY=1
                    fi
                    if [ -f $Pi0MCRAWFILE ] && [ -f $Pi0MCcorrectionFILE ]; then
                        root -b -x -q -l TaskV1/CorrectSignalMerged.C\+\+\(\"$Pi0MCRAWFILE\"\,\"$Pi0MCcorrectionFILE\"\,\"$cutSelection\"\,\"$Suffix\"\,\"Pi0\"\,kTRUE\,\"$energy\"\,\"$PERIODNAME\"\,10\)
                    else 
                        PARTLY=1
                    fi
                fi
                if [ $DoEta -eq 1 ]; then    
                    if [ -f $EtadataRAWFILE ] && [ -f $EtaMCcorrectionFILE ]; then
                        root -b -x -q -l TaskV1/CorrectSignalMerged.C\+\+\(\"$EtadataRAWFILE\"\,\"$EtaMCcorrectionFILE\"\,\"$cutSelection\"\,\"$Suffix\"\,\"Eta\"\,kFALSE\,\"$energy\"\,\"$PERIODNAME\"\,10\)
                    else 
                            PARTLY=1
                    fi
                    if [ -f $EtaMCRAWFILE ] && [ -f $EtaMCcorrectionFILE ]; then
                        root -b -x -q -l TaskV1/CorrectSignalMerged.C\+\+\(\"$EtaMCRAWFILE\"\,\"$EtaMCcorrectionFILE\"\,\"$cutSelection\"\,\"$Suffix\"\,\"Eta\"\,kTRUE\,\"$energy\"\,\"$PERIODNAME\"\,10\)
                    else 
                            PARTLY=1
                    fi
                fi
            fi
            NORMALCUTS=`expr $NORMALCUTS + 1`
        done
        
        if [ $DoPi0 -eq 1 ]; then
            root -l -b -x -q TaskV1/CutStudiesOverviewMerged.C\+\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Pi0\"\,\"kFALSE\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,\"$PERIODNAME\"\,$mode\)
            root -l -b -x -q TaskV1/CutStudiesOverviewMerged.C\+\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Pi0\"\,\"kTRUE\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,\"$PERIODNAME\"\,$mode\)
        fi
        if [ $DoEta -eq 1 ]; then
            root -l -b -x -q TaskV1/CutStudiesOverviewMerged.C\+\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Eta\"\,\"kFALSE\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,\"$PERIODNAME\"\,$mode\)
            root -l -b -x -q TaskV1/CutStudiesOverviewMerged.C\+\+\(\"CutSelection.log\"\,\"$Suffix\"\,\"Eta\"\,\"kTRUE\"\,\"$energy\"\,\"$NAMECUTSTUDIES\"\,$NORMALCUTS\,\"$PERIODNAME\"\,$mode\)
        fi
    fi        
fi

if [ $mode = 10 ] || [ $mode = 11 ]; then
    exit;
fi

if [ "$energy" != "PbPb_2.76TeV" ]; then
    if [ "$energy" != "pPb_5.023TeV" ]; then
        Pi0dataCorr=`ls $standardCutMeson/$energy/Pi0_data_GammaConvV1Correction_*.root`
        Pi0MCCorr=`ls $standardCutMeson/$energy/Pi0_MC_GammaConvV1Correction_*.root`
        GammaPi0dataCorr=`ls $standardCutGamma/$energy/Gamma_Pi0_data_GammaConvV1Correction_*.root`
        GammaPi0MCCorr=`ls $standardCutGamma/$energy/Gamma_Pi0_MC_GammaConvV1Correction_*.root`

        if [ $DoPi0InEtaBinning -eq 1 ]; then
            Pi0EtadataCorr=`ls $standardCutMeson/$energy/Pi0EtaBinning_data_GammaConvV1Correction_*.root`
            Pi0EtaMCCorr=`ls $standardCutMeson/$energy/Pi0EtaBinning_MC_GammaConvV1Correction_*.root`
            GammaPi0EtadataCorr=`ls $standardCutGamma/$energy/Gamma_Pi0EtaBinning_data_GammaConvV1Correction_*.root`
            GammaPi0EtaMCCorr=`ls $standardCutGamma/$energy/Gamma_Pi0EtaBinning_MC_GammaConvV1Correction_*.root`
        fi
        if [ $DoEta -eq 1 ]; then    
            EtadataCorr=`ls $standardCutMeson/$energy/Eta_data_GammaConvV1Correction_*.root`
            EtaMCCorr=`ls $standardCutMeson/$energy/Eta_MC_GammaConvV1Correction_*.root`
            GammaEtadataCorr=`ls $standardCutGamma/$energy/Gamma_Eta_data_GammaConvV1Correction_*.root`
            GammaEtaMCCorr=`ls $standardCutGamma/$energy/Gamma_Eta_MC_GammaConvV1Correction_*.root`
        fi
        
        CallPi0Data=\"$Pi0dataCorr\"\,\"$EtadataCorr\"\,\"$standardCutMeson\"\,\"$Suffix\"\,\"kFALSE\"\,\"Levy\"\,\"\"\,\"$energy\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"$ESTIMATEPILEUP\"
        CallPi0MC=\"$Pi0MCCorr\"\,\"$EtaMCCorr\"\,\"$standardCutMeson\"\,\"$Suffix\"\,\"kTRUE\"\,\"Levy\"\,\"\"\,\"$energy\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"$ESTIMATEPILEUP\"
        CallPi0EtaData=\"$Pi0EtadataCorr\"\,\"$EtadataCorr\"\,\"$standardCutMeson\"\,\"$Suffix\"\,\"kFALSE\"\,\"Levy\"\,\"same\"\,\"$energy\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"$ESTIMATEPILEUP\"
        CallPi0EtaMC=\"$Pi0EtaMCCorr\"\,\"$EtaMCCorr\"\,\"$standardCutMeson\"\,\"$Suffix\"\,\"kTRUE\"\,\"Levy\"\,\"same\"\,\"$energy\"\,\"$directphoton\"\,\"$OPTMINBIASEFF\"\,\"$ESTIMATEPILEUP\"

        if [ $ONLYCUTS -eq 0 ]; then 
            if [ -f $EtadataCorr ] && [ -f $Pi0dataCorr ] && [ -f $SysErrFiledata ]; then
                CreateFinalResults $CallPi0Data ;
                if [ $DoGamma -eq 1 ]; then
                    if [ $NEWGammaMacros == 0 ]; then 
                        CreateGammaFinalResults $GammaPi0dataCorr $Pi0dataCorr $standardCutMeson $Suffix Pi0 kFALSE;
                    fi    
                fi 
            else 
                PARTLY=1
            fi

            echo "have done this" 

            if [ -f $EtaMCCorr ] && [ -f $Pi0MCCorr ] && [ -f $SysErrFileMC ]; then
                CreateFinalResults $CallPi0MC
            else 
                PARTLY=1
            fi
            if [ $DoPi0InEtaBinning -eq 1 ] && [ $DoEta -eq 1 ]; then
                if [ -f $EtadataCorr ] && [ -f $Pi0EtadataCorr ] && [ -f $SysErrFiledata ] ; then
                    CreateFinalResults $CallPi0EtaData
                else 
                    PARTLY=1
                fi    
                if [ -f $EtaMCCorr ] && [ -f $Pi0EtaMCCorr ] && [ -f $SysErrFileMC ]; then
                    CreateFinalResults $CallPi0EtaMC
                else 
                    PARTLY=1
                fi
            fi
        fi    
    fi
fi
