echo "Choose option:";
echo "(0) Runwise LHC12";
echo "(1) Runwise LHC11";
echo "(2) Runwise LHC13";
echo "(3) Runwise LHC12-Trigger";
read answer
if [ $answer = 0 ]; then
    echo "Runwise LHC12 - Are you sure?";
    read answer
    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Continuing ...";
    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "Aborting ...";
            exit
    else
            echo "Command not found. Please try again.";
    fi
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12-single\"\,0\,1\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12\"\,0\,1\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12a\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12b\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12c\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12d\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12f\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12g\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12h\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12i\"\,0\,2\)
elif [ $answer = 1 ]; then
    echo "Runwise LHC11 - Are you sure?";
    read answer
    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Continuing ...";
    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "Aborting ...";
            exit
    else
            echo "Command not found. Please try again.";
    fi
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC11a\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC11a-kEMC1\"\,1\,2\)
elif [ $answer = 2 ]; then
    echo "Runwise LHC13 - Are you sure?";
    read answer
    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Continuing ...";
    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "Aborting ...";
            exit
    else
            echo "Command not found. Please try again.";
    fi
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC13g-kEMCEG1\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC13g-kEMCEG2\"\,1\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC13g\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC13g-kEMC7\"\,1\,2\)
elif [ $answer = 3 ]; then
    echo "Runwise LHC12-Trigger - Are you sure?";
    read answer
    if [ $answer = "Yes" ] || [ $answer = "Y" ] || [ $answer = "y" ] || [ $answer = "yes" ]; then
            echo "Continuing ...";
    elif [ $answer = "No" ] || [ $answer = "N" ] || [ $answer = "no" ] || [ $answer = "n" ]; then
            echo "Aborting ...";
            exit
    else
            echo "Command not found. Please try again.";
    fi
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12-kEMC7-single\"\,0\,1\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12-kEMC7\"\,0\,1\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12a-kEMC7\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12b-kEMC7\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12c-kEMC7\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12d-kEMC7\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12e-kEMC7\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12f-kEMC7\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12g-kEMC7\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12h-kEMC7\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12i-kEMC7\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12-kEMCEGA-single\"\,0\,1\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12-kEMCEGA\"\,0\,1\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12a-kEMCEGA\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12b-kEMCEGA\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12c-kEMCEGA\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12d-kEMCEGA\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12e-kEMCEGA\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12f-kEMCEGA\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12g-kEMCEGA\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12h-kEMCEGA\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12i-kEMCEGA\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12-kEMCEJE-single\"\,0\,1\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12-kEMCEJE\"\,0\,1\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12a-kEMCEJE\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12b-kEMCEJE\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12c-kEMCEJE\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12d-kEMCEJE\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12e-kEMCEJE\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12f-kEMCEJE\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12g-kEMCEJE\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12h-kEMCEJE\"\,0\,2\)
    root -x -l -b -q TaskV1/ClusterQARunwise_pp.C\+\(\"LHC12i-kEMCEJE\"\,0\,2\)
else
    echo "No valid option";
fi
