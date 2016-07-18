echo "Choose option:";
echo "(0) RunQA LHC12";
echo "(1) RunQA LHC11";
echo "(2) RunQA LHC13";
echo "(3) RunQA LHC12-Trigger";
read answer
if [ $answer = 0 ]; then
    echo "RunQA LHC12 - Are you sure?";
    read answer
    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Continuing ...";
    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "Aborting ...";
            exit
    else
            echo "Command not found. Please try again.";
    fi
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12a\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12b\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12c\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12d\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12f\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12g\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12h\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12i\"\)
    root -x -l -b -q TaskV1/ClusterQA_CellCompare.C\+\(\)
elif [ $answer = 1 ]; then
    echo "RunQA LHC11 - Are you sure?";
    read answer
    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Continuing ...";
    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "Aborting ...";
            exit
    else
            echo "Command not found. Please try again.";
    fi
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC11a\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(1\,\"LHC11a-kEMC1\"\)
elif [ $answer = 2 ]; then
    echo "RunQA LHC13 - Are you sure?";
    read answer
    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Continuing ...";
    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "Aborting ...";
            exit
    else
            echo "Command not found. Please try again.";
    fi
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC13g-kEMCEG1\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC13g-kEMCEG2\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC13g\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC13g-kEMC7\"\)
elif [ $answer = 3 ]; then
    echo "RunQA LHC12-Trigger - Are you sure?";
    read answer
    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Continuing ...";
    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "Aborting ...";
            exit
    else
            echo "Command not found. Please try again.";
    fi
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12-kEMCEJE\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12a-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12b-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12c-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12d-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12e-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12f-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12g-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12h-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12i-kEMC7\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12a-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12b-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12c-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12d-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12e-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12f-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12g-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12h-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12i-kEMCEGA\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12a-kEMCEJE\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12b-kEMCEJE\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12c-kEMCEJE\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12d-kEMCEJE\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12e-kEMCEJE\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12f-kEMCEJE\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12g-kEMCEJE\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12h-kEMCEJE\"\)
    root -x -l -b -q TaskV1/ClusterQA_pp.C\+\(0\,\"LHC12i-kEMCEJE\"\)
else
    echo "No valid option";
fi

