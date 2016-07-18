#  root -l -b -q -x TaskV1/BuildHistogramsForGammaQAAdvV1.C\+\+\(\"$2\"\,\"$5_$1\"\,0\,0\,\"PhotonQA_LHC10h_$1\"\)
#  root -l -b -q -x TaskV1/BuildHistogramsForGammaQAAdvV1.C\+\+\(\"$3\"\,\"$5_$1\"\,1\,0\,\"PhotonQA_Hijing_LHC11a_10a_bis_$1\"\)

root -l -q -b -x TaskV1/PhotonQAAdv.C\+\+\(\"PhotonQA_LHC10h_$1_Data.root\"\,\"PhotonQA_Hijing_LHC11a_10a_bis_$1_MC.root\"\,\"$5_$1\"\,\"$4\"\,\"PbPb_2.76TeV\"\,\"Hijing\"\,\"LHC10h\"\)
